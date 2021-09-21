#include "game/item_override.h"
#include "game/items.h"

namespace game {


extern "C" {
  void ItemOverride_GetItem(act::Actor* fromActor, act::Player* player, s8 incomingItemId) {
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