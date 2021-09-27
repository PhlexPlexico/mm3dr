#include "rnd/item_table.h"
#include "rnd/item_upgrade.h"
#include "rnd/item_effect.h"
#include "rnd/rHeap.h"
#include <stddef.h>

#include "z3D/z3Dvec.h"

#define ITEM_ROW( \
        baseItemId_, chestType_, itemId_,  textId_, objectId_, objectModelIdx_, cmabIndex_, \
        objectModelIdx2_, cmabIndex2_, special_, graphicId_, upgrade_, effect_, effectArg1_, effectArg2_) \
    { .baseItemId = baseItemId_, .chestType = chestType_, .itemId = itemId_, \
      .textId = textId_, .objectId = objectId_, .objectModelIdx = objectModelIdx_, .cmabIndex = cmabIndex_, \
      .objectModelIdx2 = objectModelIdx2_, .cmabIndex2 = cmabIndex2_, .special = special_, .graphicId = graphicId_, \
      .upgrade = upgrade_, .effect = effect_, .effectArg1 = effectArg1_, .effectArg2 = effectArg2_ }