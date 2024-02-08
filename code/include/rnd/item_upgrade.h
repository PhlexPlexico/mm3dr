#ifndef _RND_ITEM_UPGRADES_H
#define _RND_ITEM_UPGRADES_H
#include "game/common_data.h"
#include "rnd/item_override.h"

namespace rnd {
  GetItemID ItemUpgrade_None(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_BombBag(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_Quiver(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_Wallet(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_Magic(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_LargeMagic(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_SmallMagic(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_Sword(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_ArrowsToRupee(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_BombsToRupee(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_RefillBottle(game::SaveData*, GetItemID);
  GetItemID ItemUpgrade_CheckShield(game::SaveData*, GetItemID);
  // GetItemID ItemUpgrade_LetterToBottle(game::SaveData*, GetItemID);
}  // namespace rnd

#endif