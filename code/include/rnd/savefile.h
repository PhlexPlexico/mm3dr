#ifndef _RND_SAVEFILE_H_
#define _RND_SAVEFILE_H_

#include "common/bitfield.h"
#include "game/common_data.h"
#include "rnd/extdata.h"
#include "z3d/z3DVec.h"

// Increment the version number whenever the ExtSaveData structure is changed
#define EXTSAVEDATA_VERSION 03

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
  void SaveFile_InitExtSaveData(u32 fileBaseIndex);
  void SaveFile_LoadExtSaveData(u32 saveNumber);
  extern "C" void SaveFile_SaveExtSaveData();

  typedef struct {
    u32 version;  // Needs to always be the first field of the structure
    u32 playtimeSeconds;
    u32 isNewFile;
    u8 playedSosOnce;
    u8 playedElegyOnce;
    union GivenItemRegister {
      u16 raw;

      BitField<0, 1, u16> enNbGivenItem;
      BitField<1, 1, u16> enAlGivenItem;
      BitField<2, 1, u16> enBabaGivenItem;
      BitField<3, 1, u16> enStoneHeishiGivenItem;
      BitField<4, 1, u16> mummyDaddyGivenItem;
      BitField<5, 1, u16> enGuruGuruGivenItem;
      BitField<6, 1, u16> enYbGivenItem;
      BitField<7, 1, u16> enGegGivenItem;
      BitField<8, 1, u16> enZogGivenItem;
      BitField<9, 1, u16> enGgGivenItem;
      BitField<10, 6, u16> unused;
    };
    GivenItemRegister givenItemChecks; 
    union FairyCollectRegister {
      u8 raw;

      BitField<0, 1, u8> nct;
      BitField<1, 1, u8> woodfall;
      BitField<2, 1, u8> snowhead;
      BitField<3, 1, u8> great_bay;
      BitField<4, 1, u8> ikana;
      BitField<5, 3, u8> unused;
    };
    FairyCollectRegister fairyRewards;
    u8 chestRewarded[116][30];  // Reward table that's stored by scene and chest param/flag.
  } ExtSaveData;

  extern "C" ExtSaveData gExtSaveData;
}  // namespace rnd

#endif  //_RND_SAVEFILE_H_