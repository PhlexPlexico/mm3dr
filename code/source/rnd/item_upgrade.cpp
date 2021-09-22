#include "rnd/item_upgrade.h"
#include "rnd/item_override.h"

namespace rnd {
  GetItemID ItemUpgrade_None(game::SaveData *saveCtx, game::ItemId itemId) {
    return (GetItemID)itemId;
  }

  GetItemID ItemUpgrade_BombBag(game::SaveData *saveCtx, game::ItemId itemId) {
    switch(saveCtx->inventory.inventory_count_register.bomb_bag_upgrade) {
    case game::BombBag::NoBag:
      return GetItemID::GI_BOMB_BAG_20; // Bomb Bag
    case game::BombBag::BombBag20:
      return GetItemID::GI_BOMB_BAG_30; // Bigger Bomb Bag
    default:
      return GetItemID::GI_BOMB_BAG_40; // Biggest Bomb Bag
    }
  }

  GetItemID ItemUpgrade_Quiver(game::SaveData *saveCtx, game::ItemId itemId) {
    switch(saveCtx->inventory.inventory_count_register.quiver_upgrade) {
    case game::Quiver::NoQuiver:
      return GetItemID::GI_HEROS_BOW; // Bow
    case game::Quiver::Quiver30:
      return GetItemID::GI_LARGE_QUIVER; // Big Quiver
    default:
      return GetItemID::GI_LARGEST_QUIVER; // Biggest Quiver
    }
  }

  GetItemID ItemUpgrade_Wallet(game::SaveData *saveCtx, game::ItemId itemId) {
    switch(saveCtx->inventory.inventory_count_register.wallet_upgrade) {
    case 0:
      return GetItemID::GI_ADULT_WALLET; // Adult's Wallet
    case 1:
      return GetItemID::GI_GIANT_WALLET; // Giant's Wallet
    default:
      return GetItemID::GI_GIANT_WALLET; // Tycoon's Wallet
    }
  }

  void ItemUpgrade_Magic(game::SaveData *saveCtx, game::ItemId itemId) {
    switch (saveCtx->player.magic_num_upgrades) {
    case 0:
      saveCtx->player.magic_num_upgrades = 1; // Single Magic
    default:
      saveCtx->player.magic_num_upgrades = 2; // Double Magic
    }
  }


  GetItemID ItemUpgrade_Sword(game::SaveData *saveCtx, game::ItemId itemId) {
    switch(saveCtx->equipment.sword_shield.sword) {
    case game::SwordType::NoSword:
      return GetItemID::GI_SWORD_KOKIRI_STOLEN; // Stolen sword?
    case game::SwordType::KokiriSword:
      return GetItemID::GI_RAZOR_SWORD; // Razor sword
    case game::SwordType::RazorSword:
      return GetItemID::GI_GILDED_SWORD; // Gilded sword
    default:
      return GetItemID::GI_GILDED_SWORD; // Restore stolen sword?
    }
  }

  GetItemID ItemUpgrade_ArrowsToRupee(game::SaveData *saveCtx, game::ItemId itemId) {
    return (saveCtx->inventory.inventory_count_register.quiver_upgrade == game::Quiver::NoQuiver) ? (GetItemID)itemId : GetItemID::GI_RUPEE_BLUE; // Blue Rupee
  }

  GetItemID ItemUpgrade_BombsToRupee(game::SaveData *saveCtx, game::ItemId itemId) {
    return (saveCtx->inventory.inventory_count_register.bomb_bag_upgrade == game::BombBag::NoBag) ? (GetItemID)itemId : GetItemID::GI_RUPEE_BLUE; // Blue Rupee
  }

  // TODO: Trade quest items.
  /*
  game::ItemId ItemUpgrade_LetterToBottle(game::SaveData *saveCtx, game::ItemId itemId) {
    if (saveCtx->eventChkInf[3] & 0x0008) // "King Zora Moved Aside" //TODO: check this
      return 0xC8;                        // Redundant Letter Bottle
    if (saveCtx->items[SLOT_BOTTLE_1] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_2] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_3] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_4] == ITEM_LETTER_RUTO)
      return 0xC8; // Redundant Letter Bottle
    return itemId;
  }*/
}