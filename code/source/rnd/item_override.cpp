#include "rnd/item_override.h"
#include "rnd/icetrap.h"
#include "rnd/item_table.h"
#include "rnd/rheap.h"
#include "rnd/savefile.h"

#ifdef ENABLE_DEBUG
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  static s32 rItemOverrides_Count = 0;
  ItemOverride rItemOverrides[640] = {0};
  static game::act::Actor *rDummyActor = NULL;
  static ItemOverride rPendingOverrideQueue[3] = {0};
  static ItemOverride rActiveItemOverride = {0};
  // Accessed via hooks.
  ItemRow *rActiveItemRow = NULL;
  u32 rActiveItemGraphicId = 0x0;
  // Split active_item_row into variables for convenience in ASM
  u32 rActiveItemActionId = 0;
  u32 rActiveItemTextId = 0;
  u32 rActiveItemObjectId = 0;
  u32 rActiveItemFastChest = 0;

  static u8 rSatisfiedPendingFrames = 0;

  void ItemOverride_Init(void) {
    #ifdef ENABLE_DEBUG
    rItemOverrides[0].key.scene = 0x6F;
    rItemOverrides[0].key.type = ItemOverride_Type::OVR_COLLECTABLE;
    rItemOverrides[0].value.getItemId = 0x37;
    rItemOverrides[0].value.looksLikeItemId = 0x37;
    #endif
    while (rItemOverrides[rItemOverrides_Count].key.all != 0) {
      rItemOverrides_Count++;
    }

    // Create an actor satisfying the minimum requirements to give the player an item
    rDummyActor = (game::act::Actor *)rHeap_Alloc(sizeof(game::act::Actor));
    rDummyActor->calc_fn = (game::act::MainFunc *)1;
    rDummyActor->parent_actor = NULL;
  }

  static ItemOverride_Key ItemOverride_GetSearchKey(game::act::Actor *actor, u8 scene, u8 getItemId) {

    game::CommonData &cdata = game::GetCommonData();
    ItemOverride_Key retKey;
    retKey.all = 0;
    if (actor->actor_type == game::act::Type::Chest) {

      // XXX: Any games like H&D or chest game to not swap?
      // Don't override WINNER purple rupee in the chest minigame scene
      // if (scene == 0x11 || scene == 0x17) {
      //     u32 chestItemId = (actor->params >> 5) & 0x7F;
      //     if (chestItemId == 0x75) {
      //         return (ItemOverride_Key){ .all = 0 };
      //     }
      // }
      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_CHEST;
      retKey.flag = actor->params & 0x1F;
      return retKey;
    } else if (actor->actor_type == game::act::Type::Misc) { // Heart pieces are misc apparently
      // Only override heart pieces and keys
      u32 collectibleType = actor->params & 0xFF;
      // XXX: AFAIK These are correct. Heart piece was checked.
      if (collectibleType != 0x06 && collectibleType != 0x11) {
        return (ItemOverride_Key){.all = 0};
      }
      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_COLLECTABLE;
      retKey.flag = actor->overlay_info->info->flags;
      return retKey;
    } else if (actor->id == (game::act::Id)game::ItemId::GoldSkulltula) { // Gold Skulltula Token
      retKey.scene = (actor->params >> 8) & 0x1F;
      retKey.type = ItemOverride_Type::OVR_SKULL;
      retKey.flag = actor->params & 0xFF;
      return retKey;
      // TODO: Find grotto salesman ID.
    } else if (scene == 0x07 && actor->id == (game::act::Id)0x11A) { // Grotto Salesman
      retKey.scene = cdata.sub13s[8].data;
      retKey.type = ItemOverride_Type::OVR_GROTTO_SCRUB;
      retKey.flag = getItemId;
      return retKey;
    } else {
      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_BASE_ITEM;
      retKey.flag = getItemId;
      return retKey;
    }
  }

  ItemOverride ItemOverride_Lookup(game::act::Actor *actor, u8 scene, u8 getItemId) {
    ItemOverride_Key key = ItemOverride_GetSearchKey(actor, scene, getItemId);
    if (key.all == 0) {
      return (ItemOverride){0};
    }
    #ifdef ENABLE_DEBUG
    rnd::util::Print("%s: Our key values:\nScene %u\nType: %u\nFlag: %u\nAll: %u\nPad_: %u\n", __func__, key.scene, key.type, key.flag, key.all, key.pad_);
    rnd::util::Print("%s: Our param values:\nActor Type %#04x\nGet Item ID: %#04x\nActor ID: %#04x\n", \
      __func__, \
      actor->actor_type, \
      getItemId,
      actor->id);
    #endif
    return ItemOverride_LookupByKey(key);
  }

  ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key) {
    s32 start = 0;
    s32 end = rItemOverrides_Count - 1;
    while (start <= end) {
      s32 midIdx = (start + end) / 2;
      ItemOverride midOvr = rItemOverrides[midIdx];
      if (key.all < midOvr.key.all) {
        end = midIdx - 1;
      } else if (key.all > midOvr.key.all) {
        start = midIdx + 1;
      } else {
        return midOvr;
      }
    }
    return (ItemOverride){0};
  }

  static void ItemOverride_Activate(ItemOverride override) {
    u16 resolvedGetItemId = ItemTable_ResolveUpgrades(override.value.getItemId);
    
    ItemRow *itemRow = ItemTable_GetItemRow(resolvedGetItemId);
    u8 looksLikeItemId = override.value.looksLikeItemId;
    if (override.value.getItemId == 0x12) { // Ice trap
      looksLikeItemId = 0;
    }

    rActiveItemOverride = override;
    rActiveItemRow = itemRow;
    rActiveItemActionId = itemRow->itemId;
    rActiveItemTextId = itemRow->textId;
    rActiveItemObjectId = itemRow->objectId;
    rActiveItemGraphicId = looksLikeItemId ? ItemTable_GetItemRow(looksLikeItemId)->graphicId : itemRow->graphicId;
    rActiveItemFastChest = (u32)itemRow->chestType & 0x01;
  }

  static void ItemOverride_Clear(void) {
    rActiveItemOverride = (ItemOverride){0};
    rActiveItemRow = NULL;
    rActiveItemActionId = 0;
    rActiveItemTextId = 0;
    rActiveItemObjectId = 0;
    rActiveItemGraphicId = 0;
    rActiveItemFastChest = 0;
  }

  static void ItemOverride_PushPendingOverride(ItemOverride override) {
    for (u32 i = 0; i < ARR_SIZE(rPendingOverrideQueue); ++i) {
      if (rPendingOverrideQueue[i].key.all == 0) {
        rPendingOverrideQueue[i] = override;
        break;
      }
      if (rPendingOverrideQueue[i].key.all == override.key.all) {
        // Prevent duplicate entries
        break;
      }
    }
  }

  s32 ItemOverride_IsAPendingOverride(void) {
    return (rPendingOverrideQueue[0].key.all != 0);
  }

  void ItemOverride_PushDelayedOverride(u8 flag) {
    ItemOverride_Key key;
    key.all = 0;
    key.scene = 0xFF;
    key.type = ItemOverride_Type::OVR_DELAYED;
    key.flag = flag;
    ItemOverride override = ItemOverride_LookupByKey(key);
    if (override.key.all != 0) {
      ItemOverride_PushPendingOverride(override);
    }
  }

  static void ItemOverride_PopPendingOverride(void) {
    rPendingOverrideQueue[0] = rPendingOverrideQueue[1];
    rPendingOverrideQueue[1] = rPendingOverrideQueue[2];
    rPendingOverrideQueue[2].key.all = 0;
    rPendingOverrideQueue[2].value.all = 0;
  }

  static void ItemOverride_AfterKeyReceived(ItemOverride_Key key) {
    // TODO: Is this needed? We can have many types of trade items at once according to gear screen?
  }

  static void ItemOverride_PopIceTrap(void) {
    ItemOverride_Key key = rPendingOverrideQueue[0].key;
    ItemOverride_Value value = rPendingOverrideQueue[0].value;
    // Make Ice Trap Item IDs.
    if (value.getItemId == 0x12) {
      IceTrap_Push();
      ItemOverride_PopPendingOverride();
      ItemOverride_AfterKeyReceived(key);
    }
  }

  static u32 ItemOverride_PlayerIsReady(void) {
    // Using MMR's can receive item call - use the animation IDs to determine whether
    // we can receive item. Adjust pending frames as some items may softlock?
    game::GlobalContext *gctx = rnd::GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return 0;
    game::act::Player *player = gctx->GetPlayerActor();
    if (!player)
      return 0;
    u32 currentAniId = player->player_util.state.id;
    switch (currentAniId) {
    case 0x32D: // Rolling - Human, Goron
    case 0x11F: // Zora Rolling
    case 0x07A: // FD Rolling
    case 0x150: // Deku idle
    case 0x339: // Goron idle
    case 0x183: // Human idle
    case 0x2CF: // Zora idle
    case 0x0C2: // FD idle
    case 0x225: // Walking with Sword
    case 0x135: // Walking - Human, Deku, Zora, Goron
    case 0x155: // Walking - Human, Deku, Zora, Goron
    case 0x158: // Walking - Human, Deku, Zora, Goron
    case 0x0B9: // Walking - FD
    case 0x0DC: // Backwalking after backflip - all forms
    case 0x0BC: // Sidewalking - DF
    case 0x13D: // Sidewalking
      rSatisfiedPendingFrames++;
      break;
    default:
      rSatisfiedPendingFrames = 0;
    }
    if (rSatisfiedPendingFrames >= 2) {
      rSatisfiedPendingFrames = 0;
      return 1;
    }
    return 0;
  }

  static void ItemOverride_TryPendingItem(void) {
    ItemOverride override = rPendingOverrideQueue[0];
    game::act::Player *player = rnd::GetContext().gctx->GetPlayerActor();
    if (player) {
      if (override.key.all == 0) {
        return;
      }
      if (rDummyActor->parent_actor == NULL) {
        ItemOverride_Activate(override);
        player->grabbable_actor = rDummyActor;
        player->get_item_id = rActiveItemRow->baseItemId;
      } else {
        rDummyActor->parent_actor = NULL;
        ItemOverride_PopPendingOverride();
      }
    }
  }

  void ItemOverride_AfterItemReceived(void) {
    ItemOverride_Key key = rActiveItemOverride.key;
    if (key.all == 0) {
      return;
    }
    ItemOverride_AfterKeyReceived(key);
    ItemOverride_Clear();
  }

  void ItemOverride_Update(void) {
    // TODO: Custom models, trade items.
    /*ItemOverride_CheckStartingItem();
    ItemOverride_CheckZeldasLetter();
    IceTrap_Update();
    CustomModel_Update();*/
    if (ItemOverride_PlayerIsReady()) {
      ItemOverride_PopIceTrap();
      if (IceTrap_IsPending()) {
        IceTrap_Give();
      } else {
        ItemOverride_TryPendingItem();
      }
    }
  }

  void ItemOverride_EditDrawGetItemBeforeModelSpawn(void) {
    //TODO: Custom graphics eventually.
    /*void *cmb;

    switch (rActiveItemGraphicId)
    {
    case GID_CUSTOM_DOUBLE_DEFENSE:
      cmb = (void *)(((char *)PLAYER->giDrawSpace) + 0xA4);
      CustomModel_EditHeartContainerToDoubleDefense(cmb);
      break;
    case GID_CUSTOM_CHILD_SONGS:
      cmb = (void *)(((char *)PLAYER->giDrawSpace) + 0x2E60);
      CustomModel_SetOcarinaToRGBA565(cmb);
      break;
    case GID_CUSTOM_ADULT_SONGS:
      cmb = (void *)(((char *)PLAYER->giDrawSpace) + 0xE8);
      CustomModel_SetOcarinaToRGBA565(cmb);
      break;
    case GID_CUSTOM_SMALL_KEYS:
      cmb = (void *)(((char *)PLAYER->giDrawSpace) + 0x74);
      CustomModel_ApplyColorEditsToSmallKey(cmb, rActiveItemRow->special);
      break;
    case GID_CUSTOM_BOSS_KEYS:
      cmb = (void *)(((char *)PLAYER->giDrawSpace) + 0x78);
      CustomModel_SetBossKeyToRGBA565(cmb);
      break;
    }*/
  }

  //TODO: Get skeleanimation models.
  /*void ItemOverride_EditDrawGetItemAfterModelSpawn(SkeletonAnimationModel* model) {
    void* cmabMan;

    switch (rActiveItemGraphicId) {
        case GID_CUSTOM_CHILD_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_CHILD_SONG);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode = 0;
            model->unk_0C->curFrame = rActiveItemRow->special;
            break;
        case GID_CUSTOM_ADULT_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_ADULT_SONG);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode = 0;
            model->unk_0C->curFrame = rActiveItemRow->special;
            break;
        case GID_CUSTOM_BOSS_KEYS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS, TEXANIM_BOSS_KEY);
            TexAnim_Spawn(model->unk_0C, cmabMan);
            model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode = 0;
            model->unk_0C->curFrame = rActiveItemRow->special;
            break;
    }
  }*/

  void ItemOverride_PushDungeonReward(u8 dungeon) {
    ItemOverride_Key key = {.all = 0};
    key.scene = 0xFF;
    key.type = ItemOverride_Type::OVR_TEMPLE;
    key.flag = dungeon;
    ItemOverride override = ItemOverride_LookupByKey(key);
    ItemOverride_PushPendingOverride(override);
  }

  void ItemOverride_CheckStartingItem() {
    // TODO: Check for starting quest items?
    // use eventChkInf[0] |= 0x0001 as the check for this
    /*if (EventCheck(0x00) == 0) {
          if (gSettingsContext.linksPocketItem != LINKSPOCKETITEM_DUNGEON_REWARD) {
              ItemOverride_PushDungeonReward(0xFF); // Push Link's Pocket Reward
          }
          EventSet(0x00);
      }*/
  }

  extern "C" {

  void ItemOverride_GetItemTextAndItemID(game::act::Player *actor) {
    if (rActiveItemRow != NULL) {
      #ifdef ENABLE_DEBUG
      //rnd::util::Print("Getting Item and Text IDs.\n");
      #endif
      game::GlobalContext *gctx = rnd::GetContext().gctx;
      u16 textId = rActiveItemRow->textId;
      u8 itemId = rActiveItemRow->itemId;
      ItemTable_CallEffect(rActiveItemRow);
      gctx->ShowMessage(textId, actor);
      // Get_Item_Handler. Don't give ice traps, since it may cause UB.
      if (itemId != (u8)game::ItemId::X82) {
        rnd::util::GetPointer<int(game::GlobalContext *, game::ItemId)>(0x233BEC)(
            gctx, (game::ItemId)itemId);
      }
      ItemOverride_AfterItemReceived();
    }
  }

  void ItemOverride_GetItem(game::act::Actor *fromActor, game::act::Player *player, s8 incomingGetItemId) {
    game::GlobalContext *gctx = rnd::GetContext().gctx;
    if (!gctx)
      return;
    ItemOverride override = {0};
    s32 incomingNegative = incomingGetItemId < 0;

    #ifdef ENABLE_NOLOGIC
    s8 baseItemId = -1;
    while (true) {
      baseItemId = rnd::util::GetPointer<int(void)>(0x14F55C)();
      if (baseItemId > 0x00 && baseItemId <= 0xBA) break;
    }
    #else
    if (fromActor != NULL && incomingGetItemId != 0) {
      s8 getItemId = incomingNegative ? -incomingGetItemId : incomingGetItemId;
      override = ItemOverride_Lookup(fromActor, (u8)gctx->scene, getItemId);
    }
    if (override.key.all == 0) {
      // No override, use base game's item code
      ItemOverride_Clear();
      player->get_item_id = incomingGetItemId;
      return;
    }
    ItemOverride_Activate(override);
    s8 baseItemId = rActiveItemRow->baseItemId;
    #endif
    
    
    //s8 baseItemId = rActiveItemRow->textId;
    if (override.value.getItemId == 0x12) {
      rActiveItemRow->effectArg1 = override.key.all >> 16;
      rActiveItemRow->effectArg2 = override.key.all & 0xFFFF;
    }
    player->get_item_id = incomingNegative ? -baseItemId : baseItemId;
    return;
  }
  }
}