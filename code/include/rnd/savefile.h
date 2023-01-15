#ifndef _RND_SAVEFILE_H_
#define _RND_SAVEFILE_H_

#include "game/common_data.h"
#include "rnd/extdata.h"
#include "z3d/z3DVec.h"

// Increment the version number whenever the ExtSaveData structure is changed
#define EXTSAVEDATA_VERSION 01

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
  bool SaveFile_IsValidSettingsHealth(void);
  // extern "C" {
  void SaveFile_InitExtSaveData(u32 fileBaseIndex);
  void SaveFile_LoadExtSaveData(u32 saveNumber);
  extern "C" void SaveFile_SaveExtSaveData();

  //}

  typedef struct {
    u32 version;  // Needs to always be the first field of the structure
    u32 playtimeSeconds;
    s8 aromaGivenItem;
    s8 grannyGaveReward;
    s8 stoneMaskReward;
  } ExtSaveData;

  extern "C" ExtSaveData gExtSaveData;
}  // namespace rnd

#endif  //_RND_SAVEFILE_H_