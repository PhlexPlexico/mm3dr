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
  static ItemRow rItemTable[] = {
      ITEM_ROW((u32)GetItemID::GI_NONE, ChestType::WOODEN_SMALL, 0xFF, 0x00C4, 0x0000, 0x00, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // None Item - So we don't have to do GetItemId-1 everywhere.

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FiveBombs, 0x0014, 0x00A5, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_BombsToRupee, ItemEffect_None, (s16)-1, (s16)-1), // Bombs (5)

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FiveNuts, 0x0029, 0x0094, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Nuts (5)

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::TenBombchus, 0x0014, 0x00B0, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bombchus (10)

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Arrow, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, (s16)0, (s16)-1), // Hero's Bow

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::DekuStick, 0x0019, 0x009F, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Stick

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::LensOfTruth, 0x0042, 0x00C0, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Lens of Truth

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Hookshot, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Hookshot

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreatFairySword, 0x003B, 0x001FB, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Great Fairy Sword

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Bottle, 0x005A, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::RedPotion, 0x005B, 0x00C1, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Red Potion

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreenPotion, 0x005C, 0x00C1, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Green Potion

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BluePotion, 0x005D, 0x00C1, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Blue Potion

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Fairy, 0x005E, 0x0272, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Fairy

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::DekuPrincess, 0x005F, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Deku Princess

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Milk, 0x0060, 0x00B6, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Milk

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Fish, 0x0062, 0x00C7, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Fish

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Bug, 0x0063, 0x0137, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Bug

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BigPoe, 0x0066, 0x0139, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Big Poe

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Water, 0x0067, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Water

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::HotSpringWater, 0x0068, 0x009E, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottled Water

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::X82, 0x0014, 0x00FF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_IceTrap, (s16)-1, (s16)-1), // Ice Trap 0x13

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
  }

  void ItemTable_CallEffect(ItemRow *itemRow) {
    game::CommonData &commonData = game::GetCommonData();
    itemRow->effect(&commonData, itemRow->effectArg1, itemRow->effectArg2);
  }

} // namespace rnd
