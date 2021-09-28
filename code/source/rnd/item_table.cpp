#include "rnd/item_table.h"
#include "rnd/item_effect.h"
#include "rnd/item_override.h"
#include "rnd/item_upgrade.h"
#include "rnd/rHeap.h"
#include <stddef.h>

#include "z3D/z3Dvec.h"

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

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, 0x59, 0x0014, 0x00A5, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_BombsToRupee, ItemEffect_None, (s16)-1, (s16)-1), // Bombs (5)

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, 0x8D, 0x0029, 0x0094, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Nuts (5)

      ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, 0x98, 0x0014, 0x00B0, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bombchus (10)

      ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_SMALL, 0x10, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
               (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, (s16)0, (s16)-1), // Hero's Bow

  };

} // namespace rnd
