#include "rnd/item_upgrade.h"
#include "rnd/item_override.h"
#include "rnd/razor_sword.h"

namespace rnd {
  GetItemID ItemUpgrade_None(game::SaveData *saveCtx, GetItemID GetItemId) {
    return GetItemId;
  }

  GetItemID ItemUpgrade_BombBag(game::SaveData *saveCtx, GetItemID GetItemId) {
    switch(saveCtx->inventory.inventory_count_register.bomb_bag_upgrade) {
    case game::BombBag::NoBag:
      return GetItemID::GI_BOMB_BAG_20; // Bomb Bag
    case game::BombBag::BombBag20:
      return GetItemID::GI_BOMB_BAG_30; // Bigger Bomb Bag
    default:
      return GetItemID::GI_BOMB_BAG_40; // Biggest Bomb Bag
    }
  }

  GetItemID ItemUpgrade_Quiver(game::SaveData *saveCtx, GetItemID GetItemId) {
    switch(saveCtx->inventory.inventory_count_register.quiver_upgrade) {
    case game::Quiver::NoQuiver:
      return GetItemID::GI_HEROS_BOW; // Bow
    case game::Quiver::Quiver30:
      return GetItemID::GI_LARGE_QUIVER; // Big Quiver
    default:
      return GetItemID::GI_LARGEST_QUIVER; // Biggest Quiver
    }
  }

  GetItemID ItemUpgrade_Wallet(game::SaveData *saveCtx, GetItemID GetItemId) {
    switch(saveCtx->inventory.inventory_count_register.wallet_upgrade) {
    case 0:
      return GetItemID::GI_ADULT_WALLET; // Adult's Wallet
    case 1:
      return GetItemID::GI_GIANT_WALLET; // Giant's Wallet
    default:
      return GetItemID::GI_GIANT_WALLET; // Tycoon's Wallet
    }
  }

  GetItemID ItemUpgrade_Magic(game::SaveData *saveCtx, GetItemID GetItemId) {
    switch (saveCtx->player.magic_num_upgrades) {
    case 0:
      saveCtx->player.magic_acquired = 1;
      saveCtx->player.magic_size_type = 0;
      saveCtx->player.magic = 48;
      saveCtx->equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
      saveCtx->player.magic_num_upgrades = 0; // Single Magic
      return GetItemID::GI_MAGIC_POT_SMALL;
    default:
      saveCtx->player.magic_acquired = 1;
      saveCtx->player.magic_size_type = 0;
      saveCtx->player.magic = 96;
      saveCtx->equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
      saveCtx->player.magic_num_upgrades = 1; // Double Magic
      return GetItemID::GI_MAGIC_POT_LARGE; 
    }
  }


  GetItemID ItemUpgrade_Sword(game::SaveData *saveCtx, GetItemID GetItemId) {
    switch(saveCtx->equipment.sword_shield.sword) {
    case game::SwordType::NoSword:
      return GetItemID::GI_SWORD_KOKIRI_STOLEN; // Stolen sword?
    case game::SwordType::KokiriSword:
      RS_SetDurability();
      return GetItemID::GI_RAZOR_SWORD; // Razor sword
    case game::SwordType::RazorSword:
      return GetItemID::GI_GILDED_SWORD; // Gilded sword
    default:
      return GetItemID::GI_GILDED_SWORD; // Restore stolen sword?
    }
  }

  GetItemID ItemUpgrade_ArrowsToRupee(game::SaveData *saveCtx, GetItemID getItemId) {
    return (saveCtx->inventory.inventory_count_register.quiver_upgrade == game::Quiver::NoQuiver) ? getItemId : GetItemID::GI_RUPEE_BLUE; // Blue Rupee
  }

  GetItemID ItemUpgrade_BombsToRupee(game::SaveData *saveCtx, GetItemID getItemId) {
    return (saveCtx->inventory.inventory_count_register.bomb_bag_upgrade == game::BombBag::NoBag) ? getItemId : GetItemID::GI_RUPEE_BLUE; // Blue Rupee
  }

  // TODO: Trade quest items.
  /*
  game::ItemId ItemUpgrade_LetterToBottle(game::SaveData *saveCtx, GetItemId GetItemId) {
    if (saveCtx->eventChkInf[3] & 0x0008) // "King Zora Moved Aside" //TODO: check this
      return 0xC8;                        // Redundant Letter Bottle
    if (saveCtx->items[SLOT_BOTTLE_1] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_2] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_3] == ITEM_LETTER_RUTO || saveCtx->items[SLOT_BOTTLE_4] == ITEM_LETTER_RUTO)
      return 0xC8; // Redundant Letter Bottle
    return itemId;
  }*/
}