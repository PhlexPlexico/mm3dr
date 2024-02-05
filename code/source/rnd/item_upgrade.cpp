#include "rnd/item_upgrade.h"
#include "rnd/item_override.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
#endif
namespace rnd {
  GetItemID ItemUpgrade_None(game::SaveData* saveCtx, GetItemID GetItemId) {
    return GetItemId;
  }

  GetItemID ItemUpgrade_BombBag(game::SaveData* saveCtx, GetItemID GetItemId) {
    switch (saveCtx->inventory.inventory_count_register.bomb_bag_upgrade.Value()) {
    case game::BombBag::NoBag:
      return GetItemID::GI_BOMB_BAG_20;  // Bomb Bag
    case game::BombBag::BombBag20:
      return GetItemID::GI_BOMB_BAG_30;  // Bigger Bomb Bag
    default:
      return GetItemID::GI_BOMB_BAG_40;  // Biggest Bomb Bag
    }
  }

  GetItemID ItemUpgrade_Quiver(game::SaveData* saveCtx, GetItemID GetItemId) {
    switch (saveCtx->inventory.inventory_count_register.quiver_upgrade.Value()) {
    case game::Quiver::NoQuiver:
      return GetItemID::GI_HEROS_BOW;  // Bow
    case game::Quiver::Quiver30:
      return GetItemID::GI_LARGE_QUIVER;  // Big Quiver
    default:
      return GetItemID::GI_LARGEST_QUIVER;  // Biggest Quiver
    }
  }

  GetItemID ItemUpgrade_Wallet(game::SaveData* saveCtx, GetItemID GetItemId) {
    switch (saveCtx->inventory.inventory_count_register.wallet_upgrade.Value()) {
    case 0:
      return GetItemID::GI_ADULT_WALLET;  // Adult's Wallet
    case 1:
      return GetItemID::GI_GIANT_WALLET;  // Giant's Wallet
    default:
      return GetItemID::GI_GIANT_WALLET;  // Tycoon's Wallet
    }
  }

  GetItemID ItemUpgrade_Magic(game::SaveData* saveCtx, GetItemID GetItemId) {
    switch (saveCtx->player.magic_acquired) {
    case 0:
      return (GetItemID)0xB3;
    default:
      return (GetItemID)0x2B;
    }
  }

  GetItemID ItemUpgrade_LargeMagic(game::SaveData* saveCtx, GetItemID GetItemId) {
    return GetItemID::GI_MAGIC_POT_LARGE;
  }

  GetItemID ItemUpgrade_SmallMagic(game::SaveData* saveCtx, GetItemID GetItemId) {
    return GetItemID::GI_MAGIC_POT_SMALL;
  }

  GetItemID ItemUpgrade_Sword(game::SaveData* saveCtx, GetItemID GetItemId) {
    switch (saveCtx->equipment.sword_shield.sword) {
    case game::SwordType::NoSword:
      return GetItemID::GI_KOKIRI_SWORD;  // Stolen sword?
    case game::SwordType::KokiriSword:
      gExtSaveData.givenItemChecks.progressiveSwordUpgrade = 1;
      return GetItemID::GI_RAZOR_SWORD;  // Razor sword
    case game::SwordType::RazorSword:
      gExtSaveData.givenItemChecks.progressiveSwordUpgrade = 2;
      return GetItemID::GI_GILDED_SWORD;  // Gilded sword
    default:
      gExtSaveData.givenItemChecks.progressiveSwordUpgrade = 2;
      return GetItemID::GI_GILDED_SWORD;  // Restore stolen sword?
    }
  }

  GetItemID ItemUpgrade_ArrowsToRupee(game::SaveData* saveCtx, GetItemID getItemId) {
    return (saveCtx->inventory.inventory_count_register.quiver_upgrade == game::Quiver::NoQuiver) ?
               GetItemID::GI_RUPEE_BLUE :  // Blue Rupee
               getItemId;
  }

  GetItemID ItemUpgrade_BombsToRupee(game::SaveData* saveCtx, GetItemID getItemId) {
    return (saveCtx->inventory.inventory_count_register.bomb_bag_upgrade.Value() == game::BombBag::NoBag) ?
               GetItemID::GI_RUPEE_BLUE :  // Blue Rupee
               getItemId;
  }

  // TODO: Trade quest items.
  /*
  game::ItemId ItemUpgrade_LetterToBottle(game::SaveData *saveCtx, GetItemId GetItemId) {
    if (saveCtx->eventChkInf[3] & 0x0008) // "King Zora Moved Aside" //TODO: check this
      return 0xC8;                        // Redundant Letter Bottle
    if (saveCtx->items[SLOT_BOTTLE_1] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_2] ==
  ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_3] == ITEM_LETTER_RUTO ||
  saveCtx->items[SLOT_BOTTLE_4] == ITEM_LETTER_RUTO) return 0xC8;
  // Redundant Letter Bottle return itemId;
  }*/
}  // namespace rnd