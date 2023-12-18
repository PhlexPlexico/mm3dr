#ifndef _RND_ITEM_TABLE_H_
#define _RND_ITEM_TABLE_H_

#include "game/common_data.h"
#include "rnd/chest.h"
#include "rnd/item_override.h"

namespace rnd {
  typedef u32 (*upgradeFunc)(game::SaveData* saveCtx, GetItemID itemId);
  typedef void (*effectFunc)(game::CommonData* saveCtx, s16 arg1, s16 arg2);

  typedef struct {
    s16 baseItemId;  // Fall through ItemId for parts we wish to not
    ChestType chestType;
    u8 itemId;
    u16 textId;

    u16 objectId;
    s8 objectModelIdx;
    s8 cmabIndex;        // 0xFF if none
    s8 objectModelIdx2;  // 0xFF if none
    s8 cmabIndex2;       // 0xFF if none
    s8 special;
    /* 0xFF if none. objectMeshIdx for rupees
                                 TexAnim frame for songs
                                 key ID for small keys */

    s32 graphicId;

    upgradeFunc upgrade;

    effectFunc effect;
    s16 effectArg1;
    s16 effectArg2;
  } ItemRow;

  extern "C" ItemRow rItemTable[];
  extern "C" ItemRow* rActiveItemRow;
  extern "C" u32 rActiveItemTextId;
  extern "C" u16 rCustomDungeonItemRetrieved;
  u16 ItemTable_ResolveUpgrades(u16 itemId);
  ItemRow* ItemTable_GetItemRow(u16 itemId);
  ItemRow* ItemTable_GetItemRowFromIndex(u8 rowIndex);
  void ItemTable_SetBombchusChestType(u8 type);
  void ItemTable_CallEffect(ItemRow* itemRow);

}  // namespace rnd

#endif  //_ITEM_TABLE_H_