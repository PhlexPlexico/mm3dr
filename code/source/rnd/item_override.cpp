#include "rnd/item_override.h"
#include "game/actors/great_fairy.h"
#include "rnd/extdata.h"
#include "rnd/icetrap.h"
#include "rnd/item_table.h"
#include "rnd/rheap.h"
#include "rnd/savefile.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  static s32 rItemOverrides_Count = 0;
  ItemOverride rItemOverrides[640] = {0};
  static game::act::Actor* rDummyActor = NULL;
  static ItemOverride rPendingOverrideQueue[3] = {0};
  static ItemOverride rActiveItemOverride = {0};
  // Accessed via hooks.
  ItemRow* rActiveItemRow = NULL;
  u32 rActiveItemGraphicId = 0x0;
  // Split active_item_row into variables for convenience in ASM
  u32 rActiveItemActionId = 0;
  u32 rActiveItemTextId = 0;
  u32 rActiveItemObjectId = 0;
  u32 rActiveItemFastChest = 0;
  u16 rStoredBomberNoteTextId = 0;

  static u8 rSatisfiedPendingFrames = 10;

  void ItemOverride_Init(void) {
#ifdef ENABLE_DEBUG
    // Manual overide example code
    rItemOverrides[0].key.scene = 0x6F;
    rItemOverrides[0].key.type = ItemOverride_Type::OVR_COLLECTABLE;
    rItemOverrides[0].value.getItemId = 0x26;
    rItemOverrides[0].value.looksLikeItemId = 0x26;
    rItemOverrides[1].key.scene = 0x6C;
    rItemOverrides[1].key.type = ItemOverride_Type::OVR_COLLECTABLE;
    rItemOverrides[1].value.getItemId = 0xB2;
    rItemOverrides[1].value.looksLikeItemId = 0xB2;
    rItemOverrides[2].key.scene = 0x12;
    rItemOverrides[2].key.type = ItemOverride_Type::OVR_COLLECTABLE;
    rItemOverrides[2].value.getItemId = 0x37;
    rItemOverrides[2].value.looksLikeItemId = 0x37;
#endif
    while (rItemOverrides[rItemOverrides_Count].key.all != 0) {
      rItemOverrides_Count++;
    }

    // Create an actor satisfying the minimum requirements to give the player an item
    rDummyActor = (game::act::Actor*)rHeap_Alloc(sizeof(game::act::Actor));
    rDummyActor->calc_fn = (game::act::MainFunc*)1;
    rDummyActor->parent_actor = NULL;
  }

  static ItemOverride_Key ItemOverride_GetSearchKey(game::act::Actor* actor, u16 scene, s16 getItemId) {
    game::CommonData& cdata = game::GetCommonData();
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
      // #if defined ENABLE_DEBUG || defined DEBUG_PRINT
      //       util::Print("%s Our flag is actually %#06x and & 0x1F is %#06x\n", __func__,
      //       actor->params, actor->params & 0x1F);
      // #endif
      retKey.flag = actor->params & 0x1F;
      return retKey;
    } else if (actor->actor_type == game::act::Type::Misc) {  // Heart pieces are misc apparently
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
    } else if (actor->id == (game::act::Id)game::ItemId::GoldSkulltula) {  // Gold Skulltula Token
      retKey.scene = (actor->params >> 8) & 0x1F;
      retKey.type = ItemOverride_Type::OVR_SKULL;
      retKey.flag = actor->params & 0xFF;
      return retKey;
    } else if (scene == 0x14C0 && actor->id == (game::act::Id)0x0075) {  // Grotto Salesman
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

  ItemOverride ItemOverride_Lookup(game::act::Actor* actor, u16 scene, s16 getItemId) {
    ItemOverride_Key key = ItemOverride_GetSearchKey(actor, scene, getItemId);
    if (key.all == 0) {
      return (ItemOverride){0};
    }
    // #if defined ENABLE_DEBUG || defined DEBUG_PRINT
    //     rnd::util::Print(
    //         "%s: Our param values:\nActor Type %#04x\nGet Item ID: %#04x\nActor ID: %#06x\n",
    //         __func__, actor->actor_type, getItemId, actor->id);
    // #endif
    return ItemOverride_LookupByKey(key);
  }

  ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key) {
    s32 start = 0;
    s32 end = rItemOverrides_Count - 1;
#ifdef ENABLE_DEBUG
    return rItemOverrides[1];
#endif
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

    ItemRow* itemRow = ItemTable_GetItemRow(resolvedGetItemId);
    u8 looksLikeItemId = override.value.looksLikeItemId;

    if (override.value.getItemId == 0x12) {  // Ice trap
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
    game::GlobalContext* gctx = rnd::GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return 0;
    game::act::Player* player = gctx->GetPlayerActor();
    if (!player)
      return 0;
    u32 currentAniId = player->player_util.state.id;
    switch (currentAniId) {
    case 0x32D:  // Rolling - Human, Goron
    case 0x11F:  // Zora Rolling
    case 0x07A:  // FD Rolling
    case 0x150:  // Deku idle
    case 0x339:  // Goron idle
    case 0x183:  // Human idle
    case 0x2CF:  // Zora idle
    case 0x0C2:  // FD idle
    case 0x225:  // Walking with Sword
    case 0x135:  // Walking - Human, Deku, Zora, Goron
    case 0x155:  // Walking - Human, Deku, Zora, Goron
    case 0x158:  // Walking - Human, Deku, Zora, Goron
    case 0x0B9:  // Walking - FD
    case 0x0DC:  // Backwalking after backflip - all forms
    case 0x0BC:  // Sidewalking - DF
    case 0x13D:  // Sidewalking
      rSatisfiedPendingFrames++;
      break;
    default:
      rSatisfiedPendingFrames = 0;
    }
    if (rSatisfiedPendingFrames >= 10) {
      rSatisfiedPendingFrames = 0;
      return 1;
    }
    return 0;
  }

  static void ItemOverride_TryPendingItem(void) {
    ItemOverride override = rPendingOverrideQueue[0];
    game::act::Player* player = rnd::GetContext().gctx->GetPlayerActor();
    if (player) {
      if (override.key.all == 0) {
        return;
      }
      if (rDummyActor->parent_actor == NULL) {
        ItemOverride_Activate(override);
        player->grabbable_actor = rDummyActor;
        player->get_item_id = rActiveItemRow->baseItemId;
        ItemOverride_PopPendingOverride();
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
    // TODO: Custom graphics eventually.
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

  // TODO: Get skeleanimation models.
  /*void ItemOverride_EditDrawGetItemAfterModelSpawn(SkeletonAnimationModel* model) {
    void* cmabMan;

    switch (rActiveItemGraphicId) {
        case GID_CUSTOM_CHILD_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS,
  TEXANIM_CHILD_SONG); TexAnim_Spawn(model->unk_0C, cmabMan); model->unk_0C->animSpeed = 0.0f;
            model->unk_0C->animMode = 0;
            model->unk_0C->curFrame = rActiveItemRow->special;
            break;
        case GID_CUSTOM_ADULT_SONGS:
            cmabMan = ExtendedObject_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS,
  TEXANIM_ADULT_SONG); TexAnim_Spawn(model->unk_0C, cmabMan); model->unk_0C->animSpeed = 0.0f;
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

  s16 ItemOverride_CheckNpc(game::act::Id actorId, s16 originalGetItemId, s32 incomingNegative) {
    s16 getItemId = incomingNegative ? -originalGetItemId : originalGetItemId;
    // TODO: Granny Override here - check actor scene, and check gExtData.
    if (actorId == game::act::Id::NpcEnNb) {
      if (gExtSaveData.grannyGaveReward > 0) {
        getItemId = incomingNegative ? -0xBA : 0xBA;
      }
      gExtSaveData.grannyGaveReward++;
    } else if (actorId == game::act::Id::NpcEnBjt) {
      getItemId = incomingNegative ? -0x01 : 0x01;
    } else if (actorId == game::act::Id::NpcSwampPhotographer) {
      getItemId = incomingNegative ? -0xBA : 0xBA;
    } else if (actorId == game::act::Id::NpcInvisibleGuard) {
      if (gExtSaveData.stoneMaskReward > 0) {
        getItemId = incomingNegative ? -0xBA : 0xBA;
      }
      gExtSaveData.stoneMaskReward++;
    } else if (actorId == game::act::Id::NpcAroma) {
      gExtSaveData.aromaGivenItem++;
    }
    return getItemId;
  }

  void ItemOverride_PushPendingFairyRewardItem(game::GlobalContext* gctx, game::act::GreatFairy* fromActor,
                                               s16 incomingItemId) {
    ItemOverride override = {0};
    s32 incomingNegative = incomingItemId < 0;
    if (fromActor != NULL && incomingItemId != 0) {
      s16 getItemId = incomingNegative ? -incomingItemId : incomingItemId;
      override = ItemOverride_Lookup(fromActor, (u16)gctx->scene, getItemId);
    }

    if (override.key.all == 0) {
      ItemOverride_Clear();
      return;
    }

    ItemOverride_PushPendingOverride(override);
    if (override.value.getItemId == 0x12) {
      rActiveItemRow->effectArg1 = override.key.all >> 16;
      rActiveItemRow->effectArg2 = override.key.all & 0xFFFF;
    }
    return;
  }

  extern "C" {
  bool ItemOverride_CheckAromaGivenItem() {
    if (gExtSaveData.aromaGivenItem > 0)
      return true;
    return false;
  }

  bool ItemOverride_CheckMikauGivenItem() {
    if (gExtSaveData.mikauReward > 0)
      return true;
    return false;
  }

  void ItemOverride_GetItemTextAndItemID(game::act::Player* actor) {
    if (rActiveItemRow != NULL) {
      if (rActiveItemOverride.key.type == ItemOverride_Type::OVR_CHEST) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
        rnd::util::Print("%s: Item Override is the chest right now. Our activeItemRow itemId is %06x\n", __func__,
                         rActiveItemRow->itemId);
#endif
        if (rActiveItemRow->itemId < 0x28 && rActiveItemRow->itemId > 0x30) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
          rnd::util::Print("%s:\n", __func__);
#endif
          gExtSaveData.chestRewarded[rActiveItemOverride.key.scene][rActiveItemOverride.key.flag] = 1;
        }
      }
      game::GlobalContext* gctx = rnd::GetContext().gctx;
      // int retVal;
      u16 textId = rActiveItemRow->textId;
      u8 itemId = rActiveItemRow->itemId;
      ItemTable_CallEffect(rActiveItemRow);
      gctx->ShowMessage(textId, actor);
      // Get_Item_Handler. Don't give ice traps, since it may cause UB.
      if (itemId != (u8)game::ItemId::X82) {
        rnd::util::GetPointer<int(game::GlobalContext*, game::ItemId)>(0x233BEC)(gctx, (game::ItemId)itemId);
      }
      ItemOverride_AfterItemReceived();
    }
  }

  void ItemOverride_GetItem(game::GlobalContext* gctx, game::act::Actor* fromActor, game::act::Player* player,
                            s16 incomingGetItemId) {
    ItemOverride override = {0};
    s32 incomingNegative = incomingGetItemId < 0;
    if (fromActor != NULL && incomingGetItemId != 0) {
      // #if defined ENABLE_DEBUG || DEBUG_PRINT
      //       rnd::util::Print("%s: Our actor ID is %#06x\n", __func__, fromActor->id);
      // #endif
      s16 getItemId = ItemOverride_CheckNpc(fromActor->id, incomingGetItemId, incomingNegative);
      override = ItemOverride_Lookup(fromActor, (u16)gctx->scene, getItemId);
    }
    if (override.key.all == 0) {
      // No override, use base game's item code
      ItemOverride_Clear();
      player->get_item_id = incomingGetItemId;
      return;
    } else if (gExtSaveData.chestRewarded[override.key.scene][override.key.flag] == 1) {
      // Override was already given, use base game's item code
      ItemOverride_Clear();
      player->get_item_id = -(s16)GetItemID::GI_RUPEE_BLUE;
      return;
    }
    ItemOverride_Activate(override);
    s16 baseItemId = rActiveItemRow->baseItemId;

    // s8 baseItemId = rActiveItemRow->textId;
    if (override.value.getItemId == 0x12) {
      rActiveItemRow->effectArg1 = override.key.all >> 16;
      rActiveItemRow->effectArg2 = override.key.all & 0xFFFF;
    }

    player->get_item_id = incomingNegative ? -baseItemId : baseItemId;
    if (fromActor->actor_type != game::act::Type::Chest) {
      rStoredBomberNoteTextId = rActiveItemRow->textId;
    }
    return;
  }

  void ItemOverride_GetFairyRewardItem(game::GlobalContext* gctx, game::act::GreatFairy* fromActor,
                                       s16 incomingItemId) {
    int fairyEntrance = game::GetCommonData().sub1.entrance;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    rnd::util::Print(
        "%s: Some important info:\ngreatFairyParam: %#06x\nActor type: %#04x\nIncoming item ID: %#04x\nAnon_19: %u",
        __func__, fairyEntrance, fromActor->actor_type, incomingItemId, gExtSaveData.fairyRewards.nct);
#endif
    if (fairyEntrance == 0x4600 && gExtSaveData.fairyRewards.nct != 1) {
      gExtSaveData.fairyRewards.nct = 1;
      ItemOverride_PushPendingFairyRewardItem(gctx, fromActor, 0x86);
      ItemOverride_PushPendingFairyRewardItem(gctx, fromActor, 0x0E);
      return;
    } else if (fairyEntrance == 0x4610 && gExtSaveData.fairyRewards.woodfall != 1) {
      gExtSaveData.fairyRewards.woodfall = 1;
      ItemOverride_PushPendingFairyRewardItem(gctx, fromActor, 0x2C);
      return;
    } else if (fairyEntrance == 0x4620 && gExtSaveData.fairyRewards.snowhead != 1) {
      gExtSaveData.fairyRewards.snowhead = 1;
      ItemOverride_PushPendingFairyRewardItem(gctx, fromActor, 0x2B);
      return;
    } else if (fairyEntrance == 0x4630 && gExtSaveData.fairyRewards.great_bay != 1) {
      gExtSaveData.fairyRewards.great_bay = 1;
      ItemOverride_PushPendingFairyRewardItem(gctx, fromActor, 0xB2);
      return;
    } else if (fairyEntrance == 0x4640 && gExtSaveData.fairyRewards.ikana != 1) {
      gExtSaveData.fairyRewards.ikana = 1;
      ItemOverride_PushPendingFairyRewardItem(gctx, fromActor, 0x3B);
      return;
    }
  }

  void ItemOverride_GetSoHItem(game::GlobalContext* gctx, game::act::Actor* fromActor, s16 incomingItemId) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    rnd::util::Print("%s: Song of healing item is now being obtained. Item ID is %i\n", __func__, incomingItemId);
#endif
    if (incomingItemId == 0x7A) {
      gExtSaveData.mikauReward = 1;
    } else if (incomingItemId == 0x79) {
      gExtSaveData.darmaniReward = 1;
    } else if (incomingItemId == 0x87) {
      gExtSaveData.mummyDaddyReward = 1;
    }
    ItemOverride_GetItem(gctx, fromActor, gctx->GetPlayerActor(), incomingItemId);
    return;
  }

  void ItemOverride_RemoveTextId() {
    rStoredBomberNoteTextId = 0;
  }

  int ItemOverride_CheckInventoryItemOverride(game::ItemId currentItem) {
    if (currentItem == game::ItemId::BlastMask) {
      if (gExtSaveData.grannyGaveReward == 0) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
        rnd::util::Print("%s: Checking inventory current item is %04x and granny reward is %u\n", __func__, currentItem,
                         gExtSaveData.grannyGaveReward);
#endif
        return (int)0xFF;
      }

      else
        return (int)currentItem;
    } else if (currentItem == game::ItemId::DonGeroMask) {
      return (int)currentItem;
    }

    return (int)currentItem;
  }
  }
}  // namespace rnd
