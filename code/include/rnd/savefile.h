#ifndef _RND_SAVEFILE_H_
#define _RND_SAVEFILE_H_

#include "game/common_data.h"
#include "z3d/z3DVec.h"

namespace rnd {
  void SaveFile_SkipMinorCutscenes();
  void SaveFile_SetFastAnimationFlags();
  void SaveFile_SetStartingOwlStatues();
  void SaveFile_SetComfortOptions();
  void SaveFile_FillOverWorldMapData();
  u8 SaveFile_GetMedallionCount(void);
  u8 SaveFile_GetStoneCount(void);
  u8 SaveFile_GetDungeonCount(void);
  void SaveFile_SetStartingInventory(void);
  void SaveFile_SetTradeItemAsOwned(u8 itemId);
  void SaveFile_UnsetTradeItemAsOwned(u8 itemId);
  u32 SaveFile_TradeItemIsOwned(u8 itemId);
  void SaveFile_SetOwnedTradeItemEquipped(void);
  void SaveFile_ResetItemSlotsIfMatchesID(u8 itemSlot);
  /*void SaveFile_InitExtSaveData(u32 fileBaseIndex);
  void SaveFile_LoadExtSaveData(u32 saveNumber);
  void SaveFile_SaveExtSaveData(u32 saveNumber);*/

  // Increment the version number whenever the ExtSaveData structure is changed
  /*
  #define EXTSAVEDATA_VERSION 1

    typedef struct {
      u32 version; // Needs to always be the first field of the structure
      u32 playtimeSeconds;
    } ExtSaveData;

  #ifdef DECLARE_EXTSAVEDATA
  #define EXTERN
  #else
  #define EXTERN extern
  #endif

    EXTERN ExtSaveData gExtSaveData;*/
}  // namespace rnd

#endif  //_SAVEFILE_H_