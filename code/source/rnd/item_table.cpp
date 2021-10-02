#include "rnd/item_table.h"
#include "rnd/item_effect.h"
#include "rnd/item_override.h"
#include "rnd/item_upgrade.h"
#include "rnd/rHeap.h"
#include <stddef.h>

#include "z3D/z3Dvec.h"

extern "C" { 
  #include <3ds/svc.h>
}

namespace rnd {

#define ITEM_ROW(                                                                                     \
    baseItemId_, chestType_, itemId_, textId_, objectId_, objectModelIdx_, cmabIndex_,                \
    objectModelIdx2_, cmabIndex2_, special_, graphicId_, upgrade_, effect_, effectArg1_, effectArg2_) \
  { .baseItemId = baseItemId_, .chestType = chestType_, .itemId = itemId_, .textId = textId_,         \
    .objectId = objectId_, .objectModelIdx = objectModelIdx_, .cmabIndex = cmabIndex_,                \
    .objectModelIdx2 = objectModelIdx2_, .cmabIndex2 = cmabIndex2_, .special = special_,              \
    .graphicId = graphicId_, .upgrade = upgrade_, .effect = effect_, .effectArg1 = effectArg1_,       \
    .effectArg2 = effectArg2_ }

  // TODO: Convert to C++
  ItemRow rItemTable[] = {
      [0x00] = ITEM_ROW((u32)GetItemID::GI_NONE, ChestType::WOODEN_SMALL, 0xFF, 0x00C4, 0x0000, 0x00, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // None Item - So we don't have to do GetItemId-1 everywhere.

      [0x01] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FiveBombs, 0x0014, 0x00A5, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_BombsToRupee, ItemEffect_None, (s16)-1, (s16)-1), // Bombs (5)

      [0x02] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FiveNuts, 0x0029, 0x0094, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Nuts (5)

      [0x03] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::TenBombchus, 0x0014, 0x00B0, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bombchus (10)

      [0x04] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Arrow, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, (s16)0, (s16)-1), // Hero's Bow

      [0x05] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::DekuStick, 0x0019, 0x009F, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Stick

      [0x06] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::LensOfTruth, 0x0042, 0x00C0, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Lens of Truth

      [0x07] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Hookshot, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Hookshot

      [0x08] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreatFairySword, 0x003B, 0x001FB, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Great Fairy Sword

      [0x09] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Bottle, 0x005A, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle

      [0x0A] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::RedPotion, 0x005B, 0x00C1, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Red Potion

      [0x0B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreenPotion, 0x005C, 0x00C1, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Green Potion

      [0x0C] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BluePotion, 0x005D, 0x00C1, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Blue Potion

      [0x0D] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Fairy, 0x005E, 0x0272, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Fairy

      [0x0E] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::DekuPrincess, 0x005F, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Deku Princess

      [0x0F] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Milk, 0x0060, 0x00B6, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Milk

      [0x10] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Fish, 0x0062, 0x00C7, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Fish

      [0x11] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Bug, 0x0063, 0x0137, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Bug

      [0x12] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BigPoe, 0x0066, 0x0139, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Big Poe

      [0x13] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Water, 0x0067, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Water

      [0x14] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::HotSpringWater, 0x0068, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Hot Spring Water

      [0x15] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::X82, 0x0014, 0x00FF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_IceTrap, (s16)-1, (s16)-1), // Ice Trap 0x13

      [0x16] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::ZoraEgg, 0x0069, 0x01AE, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Zora Egg

      [0x17] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GoldDust, 0x006A, 0x01E9, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Gold Dust

      [0x18] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MagicalMushroom, 0x006B, 0x021D, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Gold Dust

      [0x19] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::SeaHorse, 0x006E, 0x01F0, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Sea Horse

      [0x1A] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::ChateauRomani, 0x006F, 0x0227, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Chateau Romani

      // XXX: Trade Item, may have to change values? Seems rather individual and leads to fishing pass.
      [0x1B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MysteryMilk, 0x00CE, 0x00B6, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Mystery Milk

      // TODO: Trade quest items
  };

  ItemRow *ItemTable_GetItemRow(u16 itemId) {
    if (itemId >= ARR_SIZE(rItemTable)) {
      return NULL;
    }
    ItemRow *itemRow = &rItemTable[18];
    if (itemRow->baseItemId == 0) {
      return NULL;
    }
    return itemRow;
  }

  ItemRow *ItemTable_GetItemRowFromIndex(u8 rowIndex) {
    return &rItemTable[rowIndex];
  }

  void ItemTable_SetBombchusChestType(u8 type) {
    //rItemTable[0x6B].chestType = type;
  }

  u16 ItemTable_ResolveUpgrades(u16 itemId) {
    game::SaveData &gSaveContext = game::GetCommonData().save;
    if (gSaveContext.has_completed_intro) {
      for (;;) {
        ItemRow *itemRow = ItemTable_GetItemRow(itemId);
        u16 newItemId = (u16)itemRow->upgrade(&gSaveContext, (GetItemID)itemId);
        if (newItemId == itemId) {
          return itemId;
        }
        itemId = newItemId;
      }
    }
    // Should not reach.
    return 0;
  }

  void ItemTable_CallEffect(ItemRow *itemRow) {
    game::CommonData &commonData = game::GetCommonData();
    itemRow->effect(&commonData, itemRow->effectArg1, itemRow->effectArg2);
  }

} // namespace rnd
