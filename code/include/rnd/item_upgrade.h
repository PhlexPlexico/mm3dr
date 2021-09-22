#ifndef _RND_ITEM_UPGRADES_H
#define _RND_ITEM_UPGRADES_H
#include "game/common_data.h"
#include "rnd/item_override.h"

namespace rnd {
  GetItemID ItemUpgrade_None(game::SaveData *saveCtx, game::ItemId itemId);
  GetItemID ItemUpgrade_BombBag(game::SaveData *saveCtx, game::ItemId itemId);
  GetItemID ItemUpgrade_Quiver(game::SaveData *saveCtx, game::ItemId itemId);
  GetItemID ItemUpgrade_Wallet(game::SaveData *saveCtx, game::ItemId itemId);
  void ItemUpgrade_Magic(game::SaveData *saveCtx, game::ItemId itemId);
  GetItemID ItemUpgrade_Sword(game::SaveData *saveCtx, game::ItemId itemId);
  GetItemID ItemUpgrade_ArrowsToRupee(game::SaveData *saveCtx, game::ItemId itemId);
  GetItemID ItemUpgrade_BombsToRupee(game::SaveData *saveCtx, game::ItemId itemId);
  //GetItemID ItemUpgrade_LetterToBottle(game::SaveData *saveCtx, game::ItemId itemId);
} // namespace rnd

#endif