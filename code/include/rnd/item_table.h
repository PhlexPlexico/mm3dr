#ifndef _RND_ITEM_TABLE_H_
#define _RND_ITEM_TABLE_H_

#include "game/common_data.h"
#include "rnd/chest.h"

namespace rnd {
  typedef u16 (*upgradeFunc)(game::SaveData *saveCtx, u16 itemId);
  typedef void (*effectFunc)(game::SaveData *saveCtx, s16 arg1, s16 arg2);

  typedef struct {
    s8 baseItemId; // Fall through ItemId for parts we wish to not
    u8 itemId;
    u16 textId;

    u16 objectId;
    //s8 objectModelIdx;
    //s8 cmabIndex; // 0xFF if none
    //s8 objectModelIdx2; // 0xFF if none
    //s8 cmabIndex2; // 0xFF if none
    //s8 special;
    /* 0xFF if none. objectMeshIdx for rupees
                                 TexAnim frame for songs
                                 key ID for small keys */
    ChestType chestType;
    s16 graphicId;

    //upgradeFunc upgrade;

    //effectFunc effect;
    //s16 effectArg1;
    //s16 effectArg2;
  } ItemRow;

  u16 ItemTable_ResolveUpgrades(u16 itemId);
  ItemRow *ItemTable_GetItemRow(u16 itemId);
  ItemRow *ItemTable_GetItemRowFromIndex(u8 rowIndex);
  void ItemTable_SetBombchusChestType(u8 type);
  void ItemTable_CallEffect(ItemRow *itemRow);

} // namespace rnd

#endif //_ITEM_TABLE_H_