#include "game/item_override.h"
#include "game/items.h"

namespace rnd {
  static s32 rItemOverrides_Count = 0;
  static ItemOverride rItemOverrides[640] = { 0 };
  static game::act::Actor* rDummyActor = NULL;
  static ItemOverride rPendingOverrideQueue[3] = { 0 };
  static ItemOverride rActiveItemOverride = { 0 };
  //TODO: Create ItemRow from the enum class.
  //ItemRow* rActiveItemRow = NULL;
  // Split active_item_row into variables for convenience in ASM
  u32 rActiveItemActionId = 0;
  u32 rActiveItemTextId = 0;
  u32 rActiveItemObjectId = 0;
  u32 rActiveItemGraphicId = 0;
  u32 rActiveItemFastChest = 0;

  static u8 rSatisfiedPendingFrames = 0;

  static ItemOverride_Key ItemOverride_GetSearchKey(game::act::Actor* actor, u8 scene, u8 itemId) {
    game::CommonData& cdata = game::GetCommonData();
    ItemOverride_Key retKey;
    if (actor->actor_type == game::act::Type::Chest) { // Chest
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
    } else if (actor->actor_type == game::act::Type::Item) { // Collectible
        // Only override heart pieces and keys
        u32 collectibleType = actor->params & 0xFF;
        // TODO: These are not correct item types? Should be 0x70 and 0x78?
        if (collectibleType != 0x70 && collectibleType != 0x78) {
            return (ItemOverride_Key){ .all = 0 };
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
        retKey.flag = itemId;
        return retKey;
    } else {
        retKey.scene = scene;
        retKey.type = ItemOverride_Type::OVR_BASE_ITEM;
        retKey.flag = itemId;
        return retKey;
    }
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
      return (ItemOverride){ 0 };
  }

  extern "C" {
    void ItemOverride_GetItem(game::act::Actor* fromActor, game::act::Player* player, s8 incomingItemId) {
      // game::GlobalContext* gctx = rnd::GetContext().gctx;
      // if (!gctx)
      //   return;
      //ItemOverride override = { 0 };
      //s32 incomingNegative = incomingItemId < 0;

      if (fromActor != NULL && incomingItemId != 0) {
          //s8 itemId = incomingNegative ? -incomingItemId : incomingItemId;
          //override = ItemOverride_Lookup(fromActor, gctx->scene, itemId);
      }


        // No override, use base game's item code
        // ItemOverride_Clear();
        player->get_item_id_maybe = (u32) GetItemID::GI_BOMBS_10;

        return;
      }
  }
}