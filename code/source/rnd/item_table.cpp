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
      [0x01] = ITEM_ROW(
          .baseItemId_=(u32)GetItemID::GI_RUPEE_BLUE, .chestType_=ChestType::WOODEN_SMALL, .itemId_=0x59, \
          .textId=0x0014, .objectId=0x00A5, .objectModelIdx=0x00, .cmabIndex=(s8)0xFF, \
          .objectModelIdx2=(s8)0xFF, .cmabIndex2=(s8)0xFF, .special=(s8)0xFF, .graphicId=0x20, \
          .upgrade=(rnd::upgradeFunc)ItemUpgrade_BombsToRupee, .effect=ItemEffect_None, \
          .effectArg1=(s16)-1, .effectArg2=(s16)-1) // Bombs (5)
  };

} // namespace rnd
