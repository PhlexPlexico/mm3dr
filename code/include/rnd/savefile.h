#ifndef _RND_SAVEFILE_H_
#define _RND_SAVEFILE_H_

#include "common/bitfield.h"
#include "game/common_data.h"
#include "rnd/extdata.h"
#include "z3d/z3DVec.h"

// Increment the version number whenever the ExtSaveData structure is changed
#define EXTSAVEDATA_VERSION 10
#define SAVEFILE_SCENES_DISCOVERED_IDX_COUNT 4
#define SAVEFILE_SPOILER_ITEM_MAX 512

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
  void SaveFile_SetSceneDiscovered(u16 sceneNum);
  void SaveFile_LoadExtSaveData(u32 saveNumber);
  u8 SaveFile_GetIsSceneDiscovered(u8 sceneNum);
  extern "C" void SaveFile_SaveExtSaveData();

  typedef struct {
    u32 version;  // Needs to always be the first field of the structure
    u32 playtimeSeconds;
    u32 isNewFile;
    u8 playedSosOnce;
    u8 playedElegyOnce;
    union GivenItemRegister {
      u32 raw;

      BitField<0, 1, u32> enNbGivenItem;
      BitField<1, 1, u32> enAlGivenItem;
      BitField<2, 1, u32> enBabaGivenItem;
      BitField<3, 1, u32> enStoneHeishiGivenItem;
      BitField<4, 1, u32> mummyDaddyGivenItem;
      BitField<5, 1, u32> enGuruGuruGivenItem;
      BitField<6, 1, u32> enYbGivenItem;
      BitField<7, 1, u32> enGegGivenItem;
      BitField<8, 1, u32> enZogGivenItem;
      BitField<9, 1, u32> enGgGivenItem;
      BitField<10, 1, u32> enOsnGivenMask;
      BitField<11, 1, u32> enOsnGivenNotebook;
      BitField<12, 1, u32> enFsnGivenItem;
      BitField<13, 1, u32> enPmGivenItem;
      BitField<14, 1, u32> enSshGivenItem;
      BitField<15, 1, u32> enDnoGivenItem;
      BitField<16, 1, u32> bgDyYoseizoGivenItem;
      BitField<17, 1, u32> enInGivenItem;
      BitField<18, 1, u32> kafeiGivenItem;
      BitField<19, 1, u32> enHgoGivenItem;
      BitField<20, 1, u32> enTruGivenItem;
      BitField<21, 1, u32> enHsGivenItem;
      BitField<22, 1, u32> enMaYtoGivenItem;
      BitField<23, 1, u32> enOskGivenItem;
      BitField<24, 1, u32> enPstGivenItem;
      BitField<25, 7, u32> unused;
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
    union TingleCollectRegister {
      u8 raw;

      BitField<0, 1, u8> clock_town_map_get;
      BitField<1, 1, u8> woodfall_map_get;
      BitField<2, 1, u8> snowhead_map_get;
      BitField<3, 1, u8> romani_map_get;
      BitField<4, 1, u8> great_bay_map_get;
      BitField<5, 1, u8> stone_tower_map_get;
      BitField<6, 2, u8> unused;
    };
    TingleCollectRegister tingleMaps;
    u32 scenesDiscovered[SAVEFILE_SCENES_DISCOVERED_IDX_COUNT];
    u8 itemCollected[SAVEFILE_SPOILER_ITEM_MAX];
    u8 chestRewarded[116][32];  // Reward table that's stored by scene and chest param/flag.
  } ExtSaveData;

  extern "C" ExtSaveData gExtSaveData;
}  // namespace rnd

#endif  //_RND_SAVEFILE_H_