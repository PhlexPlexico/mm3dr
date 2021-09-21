#include "game/item_override.h"
#include "game/items.h"

namespace rnd
{
  static s32 rItemOverrides_Count = 0;
  static ItemOverride rItemOverrides[640] = {0};
  static game::act::Actor *rDummyActor = NULL;
  static ItemOverride rPendingOverrideQueue[3] = {0};
  static ItemOverride rActiveItemOverride = {0};
  //TODO: Create ItemRow from the enum class.
  //ItemRow* rActiveItemRow = NULL;
  // Split active_item_row into variables for convenience in ASM
  u32 rActiveItemActionId = 0;
  u32 rActiveItemTextId = 0;
  u32 rActiveItemObjectId = 0;
  u32 rActiveItemGraphicId = 0;
  u32 rActiveItemFastChest = 0;

  static u8 rSatisfiedPendingFrames = 0;

  static ItemOverride_Key ItemOverride_GetSearchKey(game::act::Actor *actor, u8 scene, u8 itemId)
  {
    game::CommonData &cdata = game::GetCommonData();
    ItemOverride_Key retKey;
    if (actor->actor_type == game::act::Type::Chest)
    { // Chest
      // Don't override WINNER purple rupee in the chest minigame scene
      // if (scene == 0x10) {
      //     u32 chestItemId = (actor->params >> 5) & 0x7F;
      //     if (chestItemId == 0x75) {
      //         return (ItemOverride_Key){ .all = 0 };
      //     }
      // }

      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_CHEST;
      retKey.flag = actor->params & 0x1F;
      return retKey;
    }
    else if (actor->actor_type == game::act::Type::Item)
    { // Collectible
      // Only override heart pieces and keys
      u32 collectibleType = actor->params & 0xFF;
      // TODO: These are not correct item types? Should be 0x70 and 0x78?
      if (collectibleType != 0x70 && collectibleType != 0x78)
      {
        return (ItemOverride_Key){.all = 0};
      }
      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_COLLECTABLE;
      retKey.flag = actor->overlay_info->info->flags;
      return retKey;
    }
    else if (actor->id == (game::act::Id)game::ItemId::GoldSkulltula)
    { // Gold Skulltula Token
      retKey.scene = (actor->params >> 8) & 0x1F;
      retKey.type = ItemOverride_Type::OVR_SKULL;
      retKey.flag = actor->params & 0xFF;
      return retKey;
      // TODO: Find grotto salesman ID.
    }
    else if (scene == 0x07 && actor->id == (game::act::Id)0x11A)
    { // Grotto Salesman
      retKey.scene = cdata.sub13s[8].data;
      retKey.type = ItemOverride_Type::OVR_GROTTO_SCRUB;
      retKey.flag = itemId;
      return retKey;
    }
    else
    {
      retKey.scene = scene;
      retKey.type = ItemOverride_Type::OVR_BASE_ITEM;
      retKey.flag = itemId;
      return retKey;
    }
  }

  ItemOverride ItemOverride_LookupByKey(ItemOverride_Key key)
  {
    s32 start = 0;
    s32 end = rItemOverrides_Count - 1;
    while (start <= end)
    {
      s32 midIdx = (start + end) / 2;
      ItemOverride midOvr = rItemOverrides[midIdx];
      if (key.all < midOvr.key.all)
      {
        end = midIdx - 1;
      }
      else if (key.all > midOvr.key.all)
      {
        start = midIdx + 1;
      }
      else
      {
        return midOvr;
      }
    }
    return (ItemOverride){0};
  }

  static void ItemOverride_Activate(ItemOverride override)
  {
    //u16 resolvedItemId = ItemTable_ResolveUpgrades(override.value.itemId);
    //ItemRow* itemRow = ItemTable_GetItemRow(resolvedItemId);
    u8 looksLikeItemId = override.value.looksLikeItemId;

    if (override.value.itemId == 0x7C)
    { // Ice trap
      looksLikeItemId = 0;
    }

    rActiveItemOverride = override;
    //rActiveItemRow = itemRow;
    //rActiveItemActionId = itemRow->actionId;
    //rActiveItemTextId = itemRow->textId;
    //rActiveItemObjectId = itemRow->objectId;
    //rActiveItemGraphicId = looksLikeItemId ? ItemTable_GetItemRow(looksLikeItemId)->graphicId : itemRow->graphicId;
    //rActiveItemFastChest = itemRow->chestType & 0x01;
  }

  static void ItemOverride_Clear(void)
  {
    rActiveItemOverride = (ItemOverride){0};
    //rActiveItemRow = NULL;
    rActiveItemActionId = 0;
    rActiveItemTextId = 0;
    rActiveItemObjectId = 0;
    rActiveItemGraphicId = 0;
    rActiveItemFastChest = 0;
  }

  static void ItemOverride_PushPendingOverride(ItemOverride override)
  {
    for (u32 i = 0; i < ARR_SIZE(rPendingOverrideQueue); ++i)
    {
      if (rPendingOverrideQueue[i].key.all == 0)
      {
        rPendingOverrideQueue[i] = override;
        break;
      }
      if (rPendingOverrideQueue[i].key.all == override.key.all)
      {
        // Prevent duplicate entries
        break;
      }
    }
  }

  s32 ItemOverride_IsAPendingOverride(void)
  {
    return (rPendingOverrideQueue[0].key.all != 0);
  }

  void ItemOverride_PushDelayedOverride(u8 flag)
  {
    ItemOverride_Key key;
    key.all = 0;
    key.scene = 0xFF;
    key.type = ItemOverride_Type::OVR_DELAYED;
    key.flag = flag;
    ItemOverride override = ItemOverride_LookupByKey(key);
    if (override.key.all != 0)
    {
      ItemOverride_PushPendingOverride(override);
    }
  }

  static void ItemOverride_PopPendingOverride(void)
  {
    rPendingOverrideQueue[0] = rPendingOverrideQueue[1];
    rPendingOverrideQueue[1] = rPendingOverrideQueue[2];
    rPendingOverrideQueue[2].key.all = 0;
    rPendingOverrideQueue[2].value.all = 0;
  }

  static void ItemOverride_AfterKeyReceived(ItemOverride_Key key)
  {
    // TODO: Is this needed? We can have many types of trade items at once according to gear screen?
  }

  static void ItemOverride_PopIceTrap(void)
  {
    // TODO: Figure out ice traps?
    // ItemOverride_Key key = rPendingOverrideQueue[0].key;
    // ItemOverride_Value value = rPendingOverrideQueue[0].value;
    // if (value.itemId == 0x7C) {
    //     IceTrap_Push(key.all);
    //     ItemOverride_PopPendingOverride();
    //     ItemOverride_AfterKeyReceived(key);
    // }
  }
  static u32 ItemOverride_PlayerIsReady(void)
  {
    // TODO: Flag checks on link.
    // if ((PLAYER->stateFlags1 & 0xFCAC2485) == 0 && (PLAYER->actor.bgCheckFlags & 0x0001) &&
    //     (PLAYER->stateFlags2 & 0x000C0000) == 0 && PLAYER->actor.draw != NULL &&
    //     gGlobalContext->actorCtx.titleCtx.delayTimer == 0 && gGlobalContext->actorCtx.titleCtx.durationTimer == 0 &&
    //     gGlobalContext->actorCtx.titleCtx.alpha == 0
    //     // && (z64_event_state_1 & 0x20) == 0 //TODO
    //     // && (z64_game.camera_2 == 0) //TODO
    // ) {
    //     rSatisfiedPendingFrames++;
    // } else {
    //     rSatisfiedPendingFrames = 0;
    // }
    // if (rSatisfiedPendingFrames >= 2) {
    //     rSatisfiedPendingFrames = 0;
    //     return 1;
    // }
    // return 0;
  }

  static void ItemOverride_TryPendingItem(void)
  {
    ItemOverride override = rPendingOverrideQueue[0];
    game::act::Player *player = rnd::GetContext().gctx->GetPlayerActor();
    if (override.key.all == 0)
    {
      return;
    }

    if (rDummyActor->parent_actor == NULL)
    {
      ItemOverride_Activate(override);
      player->grabbable_actor = rDummyActor;
      // TODO: rActiveItemRow need to create item_table.
      //player->get_item_id_maybe = rActiveItemRow->baseItemId;
    }
    else
    {
      rDummyActor->parent_actor = NULL;
      ItemOverride_PopPendingOverride();
    }
  }

  void ItemOverride_AfterItemReceived(void)
  {
    ItemOverride_Key key = rActiveItemOverride.key;
    if (key.all == 0)
    {
      return;
    }
    ItemOverride_AfterKeyReceived(key);
    ItemOverride_Clear();
  }

  void ItemOverride_Update(void)
  {
    // TODO
    /*ItemOverride_CheckStartingItem();
    ItemOverride_CheckZeldasLetter();
    IceTrap_Update();
    CustomModel_Update();*/
    /*if (ItemOverride_PlayerIsReady()) {
        ItemOverride_PopIceTrap();
        if (IceTrap_IsPending()) {
            IceTrap_Give();
        } else {
            ItemOverride_TryPendingItem();
        }
    }*/
    ItemOverride_TryPendingItem();
  }

  void ItemOverride_GetItemTextAndItemID(game::act::Actor *actor)
  {
    // TODO: rActiveItemRow need to create item_table.
    /*if (rActiveItemRow != NULL) {
        u16 textId = rActiveItemRow->textId;
        u8 actionId = rActiveItemRow->actionId;

        ItemTable_CallEffect(rActiveItemRow);
        if (actionId == ITEM_SKULL_TOKEN) {
            Item_Give(gGlobalContext, actionId);
            DisplayTextbox(gGlobalContext, textId, actor);
        } else {
            DisplayTextbox(gGlobalContext, textId, actor);
            Item_Give(gGlobalContext, actionId);
        }
        ItemOverride_AfterItemReceived();
    }*/
  }

  void ItemOverride_EditDrawGetItemBeforeModelSpawn(void)
  {
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
    ItemOverride_Key key = { .all = 0 };
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

  extern "C"
  {
    void ItemOverride_GetItem(game::act::Actor *fromActor, game::act::Player *player, s8 incomingItemId)
    {
      game::GlobalContext *gctx = rnd::GetContext().gctx;
      if (!gctx)
        return;
      ItemOverride override = {0};
      s32 incomingNegative = incomingItemId < 0;

      if (fromActor != NULL && incomingItemId != 0)
      {
        s8 itemId = incomingNegative ? -incomingItemId : incomingItemId;
        //override = ItemOverride_Lookup(fromActor, gctx->scene, itemId);
      }

      // No override, use base game's item code
      ItemOverride_Clear();
      player->get_item_id_maybe = (u32)GetItemID::GI_BOMBCHUS_10;
      return;
    }
  }
}