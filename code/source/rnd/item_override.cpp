#include "rnd/item_override.h"
#include "game/actors/great_fairy.h"
#include "rnd/extdata.h"
#include "rnd/icetrap.h"
#include "rnd/item_table.h"
#include "rnd/rheap.h"
#include "rnd/savefile.h"
#include "rnd/spoiler_data.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  static s32 rItemOverrides_Count = 0;
  static game::act::Id storedActorId = game::act::Id::Player;
  ItemOverride rItemOverrides[640] = {0};
  static game::act::Actor* rDummyActor = NULL;
  static ItemOverride rPendingOverrideQueue[3] = {0};
  static ItemOverride rActiveItemOverride = {0};
  // Accessed via hooks.
  ItemRow* rActiveItemRow = NULL;
  u32 rActiveItemGraphicId = 0x0;
  // Split active_item_row into variables for convenience in ASM
  u32 rActiveItemActionId = 0;
  u32 rActiveItemObjectModelIdx = 0x0;
  u32 rActiveItemTextId = 0;
  u32 rActiveItemObjectId = 0;
  u32 rActiveItemFastChest = 0;
  u16 rStoredTextId = 0;
  u16 rCustomDungeonItemRetrieved = 0;

  static u8 rSatisfiedPendingFrames = 0;

  void ItemOverride_Init(void) {
#ifdef ENABLE_DEBUG
    // Manual overide example code
    rItemOverrides[0].key.scene = 0x6F;
    rItemOverrides[0].key.type = ItemOverride_Type::OVR_COLLECTABLE;
    rItemOverrides[0].value.getItemId = 0x26;
    rItemOverrides[0].value.looksLikeItemId = 0x26;
    rItemOverrides[1].key.scene = 0x26;
    rItemOverrides[1].key.type = ItemOverride_Type::OVR_COLLECTABLE;
    rItemOverrides[1].value.getItemId = 0xB9;
    rItemOverrides[1].value.looksLikeItemId = 0xB9;
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
      retKey.flag = actor->params & 0x1F;
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
    } else if (actor->id == (game::act::Id)game::ItemId::GoldSkulltula) {  // Gold Skulltula Token
      retKey.scene = (actor->params >> 8) & 0x1F;
      retKey.type = ItemOverride_Type::OVR_SKULL;
      retKey.flag = actor->params & 0xFF;
    } else if (scene == 0x14C0 && actor->id == (game::act::Id)0x0075) {  // Grotto Salesman
      retKey.scene = cdata.sub13s[8].data;
      retKey.type = ItemOverride_Type::OVR_GROTTO_SCRUB;
      retKey.flag = getItemId;
    } else {
      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_BASE_ITEM;
      retKey.flag = getItemId;
    }
    return retKey;
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
    // XXX: Maybe create function for progressive items so that the item drawn is correct?
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
    rCustomDungeonItemRetrieved = 0;
    storedActorId = game::act::Id::Player;
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
    case 0x07A:  // Rolling - FD
    case 0x0B9:  // Walking - FD
    case 0x0BA:  // Sidewalking - FD
    case 0x0C2:  // Idle - FD
    case 0x0C5:  // Slow Walking - FD
    case 0x0DC:  // Backwalking - Human, Deku, Zora, Goron, FD
    case 0x11F:  // Rolling - Human, Zora, Goron Rolling
    case 0x135:  // Walking - Human, Deku, Zora, Goron
    case 0x13D:  // Sidewalking - Human, Deku, Zora, Goron
    case 0x150:  // Idle - Deku
    case 0x155:  // ESS Maybe - Human, Deku, Zora, Goron
    case 0x158:  // Slow Walking - Human, Deku, Zora, Goron
    case 0x183:  // Idle - Human
    case 0x225:  // Walking with Weapon/Shield Drawn - Human
    case 0x2CF:  // Idle - Zora
    case 0x32D:  // Uncurling - Goron
    case 0x339:  // Idle - Goron
      rSatisfiedPendingFrames++;
      break;
    default:
      rSatisfiedPendingFrames = 0;
      break;
    }
    if (rSatisfiedPendingFrames >= 2) {
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
    SetExtData();
    ItemOverride_AfterKeyReceived(key);
    SpoilerLog_UpdateIngameLog(key.type, key.scene, key.flag);
    //#if ENABLE_DEBUG || DEBUG_PRINT
    // rnd::util::Print(
    //         "%s: Our key values:\nKey Type %#04x\nKey Scene: %#04x\nKey Flag: %#06x\n",
    //         key.type, key.scene, key.flag);
    //#endif
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
    if (actorId == game::act::Id::NpcEnNb) {
      if (gExtSaveData.givenItemChecks.enNbGivenItem > 0) {
        getItemId = incomingNegative ? -0xBA : 0xBA;
      }
    } else if (actorId == game::act::Id::NpcEnBjt) {
      getItemId = incomingNegative ? -0x01 : 0x01;
    } else if (actorId == game::act::Id::NpcSwampPhotographer) {
      getItemId = incomingNegative ? -0xBA : 0xBA;
    } else if (actorId == game::act::Id::NpcInvisibleGuard) {
      if (gExtSaveData.givenItemChecks.enStoneHeishiGivenItem > 0) {
        getItemId = incomingNegative ? -0xBA : 0xBA;
      }
    } else if (actorId == game::act::Id::EnPst) {
      getItemId = incomingNegative ? -0xBA : 0xBA;
    } else if (actorId == game::act::Id::EnDns) {
      // Business scrub salesmen in grotto.
      // Same scene as gossips so need to set item manually.
      getItemId = incomingNegative ? -0x01 : 0x01;
    } else if (getItemId == static_cast<s16>(rnd::GetItemID::GI_MASK_CAPTAINS_HAT)) {
      gExtSaveData.givenItemChecks.enOskGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnPst) {
      getItemId = incomingNegative ? -0xBA : 0xBA;
    }

    return getItemId;
  }

  void SetExtData() {
    if (storedActorId == game::act::Id::NpcEnNb) {
      gExtSaveData.givenItemChecks.enNbGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcInvisibleGuard) {
      gExtSaveData.givenItemChecks.enStoneHeishiGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcAroma) {
      gExtSaveData.givenItemChecks.enAlGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcEnGuruGuru) {
      gExtSaveData.givenItemChecks.enGuruGuruGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcEnYb) {
      gExtSaveData.givenItemChecks.enYbGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcEnBaba) {
      gExtSaveData.givenItemChecks.enBabaGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcEnFsn) {
      gExtSaveData.givenItemChecks.enFsnGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcEnPm) {
      gExtSaveData.givenItemChecks.enPmGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnSsh) {
      gExtSaveData.givenItemChecks.enSshGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnDno) {
      gExtSaveData.givenItemChecks.enDnoGivenItem = 1;
    } else if (storedActorId == game::act::Id::NpcGreatFairy) {
      gExtSaveData.givenItemChecks.bgDyYoseizoGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnIn) {
      gExtSaveData.givenItemChecks.enInGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnHs) {
      gExtSaveData.givenItemChecks.enHsGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnHgo) {
      gExtSaveData.givenItemChecks.enHgoGivenItem = 1;
    } else if (storedActorId == game::act::Id::EnTru) {
      gExtSaveData.givenItemChecks.enTruGivenItem = 1;
    }
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

  void ItemOverride_RevealMapBasedOnId(u8 getItemMapId) {
    game::SaveData& saveData = game::GetCommonData().save;
    switch (getItemMapId) {
    case 0xB4:
      saveData.overworld_map_data[1] = 0x30;
      saveData.overworld_map_data[2] = 0xA6;
      saveData.overworld_map_data[3] = 0x52;
      saveData.overworld_map_data[4] = 0x01;
      saveData.overworld_map_data[5] = 0x62;
      saveData.overworld_map_data[6] = 0x11;
      saveData.overworld_map_data[7] = 0x02;
      saveData.overworld_map_data[8] = 0x08;
      saveData.overworld_map_data[10] = 0x18;
      saveData.overworld_map_data[12] = 0x0A;
      saveData.overworld_map_data[13] = 0xF1;
      saveData.overworld_map_data[14] = 0x01;
      saveData.overworld_map_get_flags_0x3F_for_all = saveData.overworld_map_get_flags_0x3F_for_all | 1;
      saveData.anonymous_162 = saveData.anonymous_162 | 3;
      break;
    case 0xB5:
      saveData.overworld_map_data[0] = 0x01;
      saveData.overworld_map_data[1] = 0x04;
      saveData.overworld_map_data[4] = 0x90;
      saveData.overworld_map_data[5] = 0x08;
      saveData.overworld_map_data[7] = 0x40;
      saveData.overworld_map_data[8] = 0x61;
      saveData.overworld_map_data[10] = 0x84;
      saveData.overworld_map_data[14] = 0x02;
      saveData.overworld_map_get_flags_0x3F_for_all = saveData.overworld_map_get_flags_0x3F_for_all | 2;
      saveData.anonymous_162 = saveData.anonymous_162 | 0x1C;
      break;
    case 0xB6:
      saveData.overworld_map_data[5] = 0x10;
      saveData.overworld_map_data[6] = 0x04;
      saveData.overworld_map_data[7] = 0x20;
      saveData.overworld_map_data[9] = 0x61;
      saveData.overworld_map_data[10] = 0x01;
      saveData.overworld_map_data[11] = 0x7C;
      saveData.overworld_map_data[13] = 0x08;
      saveData.overworld_map_get_flags_0x3F_for_all = saveData.overworld_map_get_flags_0x3F_for_all | 4;
      saveData.anonymous_162 = saveData.anonymous_162 | 0xE0;
      break;
    case 0xB7:
      saveData.overworld_map_data[2] += 0x01;
      saveData.overworld_map_data[4] += 0x04;
      saveData.overworld_map_data[6] += 0x20;
      saveData.overworld_map_data[8] += 0x06;
      saveData.overworld_map_data[13] += 0x04;
      saveData.overworld_map_get_flags_0x3F_for_all = saveData.overworld_map_get_flags_0x3F_for_all | 8;
      saveData.anonymous_162 = saveData.anonymous_162 | 0x100;
      break;
    case 0xB8:
      saveData.overworld_map_data[2] += 0x10;
      saveData.overworld_map_data[4] += 0x28;
      saveData.overworld_map_data[5] += 0x81;
      saveData.overworld_map_data[6] += 0x88;
      saveData.overworld_map_data[7] += 0x19;
      saveData.overworld_map_data[9] += 0x14;
      saveData.overworld_map_data[14] += 0x04;
      saveData.overworld_map_get_flags_0x3F_for_all = saveData.overworld_map_get_flags_0x3F_for_all | 0x10;
      saveData.anonymous_162 = saveData.anonymous_162 | 0x1E00;
      break;
    case 0xB9:
      saveData.overworld_map_data[2] += 0x08;
      saveData.overworld_map_data[3] += 0x20;
      saveData.overworld_map_data[9] += 0x88;
      saveData.overworld_map_data[10] += 0x62;
      saveData.overworld_map_data[11] += 0x03;
      saveData.overworld_map_data[12] += 0x01;
      saveData.overworld_map_get_flags_0x3F_for_all = saveData.overworld_map_get_flags_0x3F_for_all | 0x20;
      saveData.anonymous_162 = saveData.anonymous_162 | 0x6000;
      break;
    default:
      break;
    }
    return;
  }

  extern "C" {
  bool ItemOverride_CheckAromaGivenItem() {
    if (gExtSaveData.givenItemChecks.enAlGivenItem > 0)
      return true;
    return false;
  }

  bool ItemOverride_CheckMikauGivenItem() {
    if (gExtSaveData.givenItemChecks.enZogGivenItem > 0)
      return true;
    return false;
  }

  bool ItemOverride_CheckDarmaniGivenItem() {
    if (gExtSaveData.givenItemChecks.enGgGivenItem > 0)
      return true;
    return false;
  }

  void ItemOverride_GetItemTextAndItemID(game::act::Player* actor) {
    if (rActiveItemRow != NULL) {
      if (rActiveItemOverride.key.type == ItemOverride_Type::OVR_CHEST) {
        // Check and see if we have trade items or repeatable bottles and add to the array.
        if (rActiveItemRow->itemId < 0x28 || (rActiveItemRow->itemId > 0x30 && rActiveItemRow->itemId < 0x9f)) {
          gExtSaveData.chestRewarded[rActiveItemOverride.key.scene][rActiveItemOverride.key.flag] = 1;
        }
      }
      game::GlobalContext* gctx = rnd::GetContext().gctx;
      u16 textId = rActiveItemRow->textId;
      u8 itemId = rActiveItemRow->itemId;
      ItemTable_CallEffect(rActiveItemRow);
      // Only check if we have the ID set, that means text is displayed elsewhere.
      if (rStoredTextId == 0)
        gctx->ShowMessage(textId, actor);
      // Get_Item_Handler. Don't give ice traps, since it may cause UB.
      if (itemId != (u8)game::ItemId::None) {
        rnd::util::GetPointer<int(game::GlobalContext*, game::ItemId)>(0x233BEC)(gctx, (game::ItemId)itemId);
        // Since the regular get item handler does not take care of this situation, we need to do it manually.
        if (rActiveItemOverride.value.getItemId > 0xB3 && rActiveItemOverride.value.getItemId < 0xBA)
          ItemOverride_RevealMapBasedOnId(rActiveItemOverride.value.getItemId);
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
      storedActorId = fromActor->id;
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
    // Weird edge case with the way text and masks are handled with Couples' Mask.
    // Set the text and apply it later in a different patch.
    if (incomingGetItemId == 0x85) {
      rStoredTextId = rActiveItemRow->textId;
    }
    return;
  }

  void ItemOverride_GetFairyRewardItem(game::GlobalContext* gctx, game::act::GreatFairy* fromActor,
                                       s16 incomingItemId) {
    int fairyEntrance = game::GetCommonData().sub1.entrance;
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
    if (incomingItemId == 0x7A) {
      gExtSaveData.givenItemChecks.enZogGivenItem = 1;
    } else if (incomingItemId == 0x79) {
      gExtSaveData.givenItemChecks.enGgGivenItem = 1;
    } else if (incomingItemId == 0x87) {
      gExtSaveData.givenItemChecks.mummyDaddyGivenItem = 1;
    } else if (incomingItemId == 0x78) {
      gExtSaveData.givenItemChecks.enOsnGivenMask = 1;
    } else if (incomingItemId == 0x50) {
      fromActor = gctx->GetPlayerActor();
    } else if (incomingItemId == 0x85) {
      gExtSaveData.givenItemChecks.kafeiGivenItem = 1;
    }
    ItemOverride_GetItem(gctx, fromActor, gctx->GetPlayerActor(), incomingItemId);
    return;
  }

  void ItemOverride_RemoveTextId() {
    rStoredTextId = 0;
  }

  int ItemOverride_CheckInventoryItemOverride(game::ItemId currentItem) {
    if (currentItem == game::ItemId::BlastMask && gExtSaveData.givenItemChecks.enBabaGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::BremenMask && gExtSaveData.givenItemChecks.enGuruGuruGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::KamaroMask && gExtSaveData.givenItemChecks.enYbGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::DonGeroMask && gExtSaveData.givenItemChecks.enGegGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::ZoraMask && gExtSaveData.givenItemChecks.enZogGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::LetterToMama && gExtSaveData.givenItemChecks.enBabaGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::KeatonMask && gExtSaveData.givenItemChecks.enFsnGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::PostmanHat && gExtSaveData.givenItemChecks.enPmGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::StoneMask && gExtSaveData.givenItemChecks.enStoneHeishiGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::MaskOfTruth && gExtSaveData.givenItemChecks.enSshGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::MaskOfScents && gExtSaveData.givenItemChecks.enDnoGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::GreatFairyMask && gExtSaveData.givenItemChecks.bgDyYoseizoGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::GaroMask && gExtSaveData.givenItemChecks.enInGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::PictographBox && gExtSaveData.givenItemChecks.enTruGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::BunnyHood && gExtSaveData.givenItemChecks.enHsGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::GibdoMask && gExtSaveData.givenItemChecks.enHgoGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::RomaniMask && gExtSaveData.givenItemChecks.enMaYtoGivenItem == 0) {
      return (int)0xFF;
    } else if (currentItem == game::ItemId::CaptainHat && gExtSaveData.givenItemChecks.enOskGivenItem == 0) {
      return (int)0xFF;
    }
    return (int)currentItem;
  }
  void ItemOverride_SwapSoHGetItemText(game::GlobalContext* gctx, u16 textId, game::act::Actor* fromActor) {
    // Check which text ID is coming in. If it's any mask from Song of Healing, replace it with active item text.
    if (textId == 0x79 || textId == 0x7a || textId == 0x87 || textId == 0x78) {
      return;
    } else if (textId == 0x85) {
      gctx->ShowMessage(rStoredTextId);
      rStoredTextId = 0;
    } else
      gctx->ShowMessage(textId);
    return;
  }

  bool ItemOverride_CheckTingleMaps(u16 mapId, game::GlobalContext* gctx) {
    switch (mapId) {
    case 0x1:
      if (gExtSaveData.tingleMaps.clock_town_map_get == 0) {
        gExtSaveData.tingleMaps.clock_town_map_get = 1;
        return true;
      }
      break;
    case 0x2:
      if (gExtSaveData.tingleMaps.woodfall_map_get == 0) {
        gExtSaveData.tingleMaps.woodfall_map_get = 1;
        return true;
      }
      break;
    case 0x4:
      if (gExtSaveData.tingleMaps.snowhead_map_get == 0) {
        gExtSaveData.tingleMaps.snowhead_map_get = 1;
        return true;
      }
      break;
    case 0x8:
      if (gExtSaveData.tingleMaps.romani_map_get == 0) {
        gExtSaveData.tingleMaps.romani_map_get = 1;
        return true;
      }
      break;
    case 0x10:
      if (gExtSaveData.tingleMaps.great_bay_map_get == 0) {
        gExtSaveData.tingleMaps.great_bay_map_get = 1;
        return true;
      }
      break;
    case 0x20:
      if (gExtSaveData.tingleMaps.stone_tower_map_get == 0) {
        gExtSaveData.tingleMaps.stone_tower_map_get = 1;
        return true;
      }
      break;
    default:
      return false;
    }
    return false;
  }

  void ItemOverride_SetGrogExtData() {
    gExtSaveData.givenItemChecks.enHsGivenItem = 1;
    return;
  }
  }
}  // namespace rnd
