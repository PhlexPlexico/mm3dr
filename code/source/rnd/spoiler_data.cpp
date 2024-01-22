#include "rnd/spoiler_data.h"
#include "game/common_data.h"
#include "rnd/item_override.h"
#include "rnd/settings.h"
#include "z3d/z3DVec.h"

namespace rnd {
  SpoilerData gSpoilerData = {0};
  SpoilerDataLocs gSpoilerDataLocs[SPOILER_LOCDATS] = {0};

  SpoilerItemLocation* SpoilerData_ItemLoc(u16 itemIndex) {
    return &gSpoilerDataLocs[itemIndex / SPOILER_ITEMS_MAX].ItemLocations[itemIndex % SPOILER_ITEMS_MAX];
  }

  SpoilerItemCollectType SpoilerData_CollectType(u16 itemIndex) {
    return gSpoilerData.ItemLocations[itemIndex].CollectType;
  }

  char* SpoilerData_StringData(u16 itemIndex) {
    return gSpoilerDataLocs[itemIndex / SPOILER_ITEMS_MAX].StringData;
  }

  char* SpoilerData_GetItemLocationString(u16 itemIndex) {
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].LocationStrOffset];
  }

  char* SpoilerData_GetItemNameString(u16 itemIndex) {
    return &gSpoilerData.StringData[gSpoilerData.ItemLocations[itemIndex].ItemStrOffset];
  }

  SpoilerItemLocation GetSpoilerItemLocation(u8 sphere, u16 itemIndex) {
    return gSpoilerData
        .ItemLocations[gSpoilerData.SphereItemLocations[gSpoilerData.Spheres[sphere].ItemLocationsOffset]];
  }

  u8 SpoilerData_ChestCheck(SpoilerItemLocation itemLoc) {
    return -1;
  }

  u8 SpoilerLog_UpdateIngameLog(ItemOverride_Type type, u8 scene, u8 flag) {
    // SpoilerData currentCheck = {0};
    for (int i = 0; i < gSpoilerData.ItemLocationsCount; i++) {
      if (gSpoilerData.ItemLocations[i].LocationScene == scene && gSpoilerData.ItemLocations[i].OverrideType == type &&
          gSpoilerData.ItemLocations[i].LocationFlag == flag) {
        gSpoilerData.ItemLocations[i].Collected = true;
        // Since it's not saved here, we need to return
        gExtSaveData.itemCollected[i] = 1;
      }
    }
    return -1;
  }

  u8 SpoilerData_CollectableCheck(SpoilerItemLocation itemLoc) {
    // TODO: Implement Collectable Checking. no need to use bits as we have
    // builtin BitField classes.
    // Reference:
    // https://github.com/gamestabled/OoT3D_Randomizer/blob/e53be23c14090b15c6c39e08933ca7af54f747f7/code/src/spoiler_data.c#L34-L41
    return -1;
  }

  // Shop checks, will need to be decomped, most likely in common_data.h.
  u8 SpoilerData_ItemGetInfCheck(u8 slot) {
    // TODO: Reimplement GetInfCheck. no need to use bits as we have
    // builtin BitField classes.
    // Reference:
    // https://github.com/gamestabled/OoT3D_Randomizer/blob/e53be23c14090b15c6c39e08933ca7af54f747f7/code/src/spoiler_data.c#L43-L49
    return -1;
  }

  // Event flags, will need to be decomped in common_data.h.
  u8 SpoilerData_InfTableCheck(u8 offset, u8 bit) {
    // TODO: Discern all event flags.
    // TODO: Reimplement with BitField class.
    // Reference:
    // https://github.com/gamestabled/OoT3D_Randomizer/blob/e53be23c14090b15c6c39e08933ca7af54f747f7/code/src/spoiler_data.c#L51-L57
    return -1;
  }

  // Once again, most likely in SaveData, to be decomped.
  u8 SpoilerData_QuestItemCheck(u8 slot) {
    // TODO: Discern all event flags.
    // TODO: Reimplement with BitField class.
    // Reference:
    // https://github.com/gamestabled/OoT3D_Randomizer/blob/e53be23c14090b15c6c39e08933ca7af54f747f7/code/src/spoiler_data.c#L59-L62
    return -1;
  }

  // Item upgrades.
  // TODO: Implement.
  u8 SpoilerData_UpgradeCheck(u8 bit) {
    return -1;
  }

  // TODO: Decomp/Implmenet cow flags.
  u8 SpoilerData_CowCheck(SpoilerItemLocation itemLoc) {
    return -1;
  }

  // TODO: Decomp/implement fishing flags.
  u8 SpoilerData_FishingCheck(SpoilerItemLocation itemLoc) {
    return -1;
  }

  // TODO: Decomp/implement scrub location/checks.
  u8 SpoilerData_ScrubCheck(SpoilerItemLocation itemLoc) {
    return -1;
  }

  // TODO: Decomp shop/items.
  u8 SpoilerData_ShopItemCheck(SpoilerItemLocation itemLoc) {
    return -1;
  }

  // TODO: Decomp bean daddy.
  u8 SpoilerData_MagicBeansCheck(SpoilerItemLocation itemLoc) {
    return -1;
  }

  u8 SpoilerData_GetIsItemLocationCollected(u16 itemIndex) {
    if (itemIndex >= gSpoilerData.ItemLocationsCount) {
      return 0;
    }

    SpoilerItemLocation itemLoc = gSpoilerData.ItemLocations[itemIndex];
    if (itemLoc.Collected == true) {
      return 1;
    } else if (gExtSaveData.itemCollected[itemIndex] == 1) {
      return 1;
    }
    if (itemLoc.CollectionCheckType == SPOILER_CHK_ALWAYS_COLLECTED) {
      return 1;
    }
    if (itemLoc.CollectionCheckType == SPOILER_CHK_NONE) {
      return 0;
    }
    return 0;
    /*
    // game::SaveData &gSaveContext = game::GetCommonData().save;
    switch (itemLoc.CollectionCheckType) {
    case SPOILER_CHK_NONE: {  // Not ever 'collectable' (Ganon, or any item that didn't have a type
                              // set)
      return 0;
    }
    case SPOILER_CHK_ALWAYS_COLLECTED: {  // Items that are considered always collected, like Link's
                                          // Pocket
      return 1;
    }
    case SPOILER_CHK_CHEST: {  // Chest
      return rnd::SpoilerData_ChestCheck(itemLoc);
    }
    case SPOILER_CHK_COLLECTABLE: {  // Placed in world, saved in the collect flags of a scene
      return SpoilerData_CollectableCheck(itemLoc);
    }
    case SPOILER_CHK_SWAMP_SKULLTULA: {  // Swamp skulltula
      // gSaveContext.skulltulas_collected.swamp_count
      return -1;
    }
    case SPOILER_CHK_OCEAN_SKULLTULA: {  // Ocean skulltula
      // gSaveContext.skulltulas_collected.ocean_count
      return -1;
    }
    case SPOILER_CHK_STRAY_FAIRY: {
      // gSaveContext.strayfairies_collected
      return -1;
    }
    case SPOILER_CHK_ITEM_GET_INF: {  // Check a flag set in item_get_inf
      return SpoilerData_ItemGetInfCheck(itemLoc.LocationFlag);
    }
    case SPOILER_CHK_EVENT_CHK_INF: {  // Check a flag set in event_check_inf
      return -1;
      // TODO: Implement EventCheck.
      // return EventCheck(itemLoc.LocationFlag) != 0;
    }
    case SPOILER_CHK_INF_TABLE: {  // Check a flag set in event_check_inf
      return SpoilerData_InfTableCheck(itemLoc.LocationScene, itemLoc.LocationFlag);
    }
    case SPOILER_CHK_COW: {
      return SpoilerData_CowCheck(itemLoc);
    }
    case SPOILER_CHK_MINIGAME: {
      return SpoilerData_FishingCheck(itemLoc);
    }
    case SPOILER_CHK_SCRUB: {
      return SpoilerData_ScrubCheck(itemLoc);
    }

    case SPOILER_CHK_SHOP_ITEM: {
      return SpoilerData_ShopItemCheck(itemLoc);
    }
    case SPOILER_CHK_MAGIC_BEANS: {
      return SpoilerData_MagicBeansCheck(itemLoc);
    }
    default: {
      return 0;
    }
    }
    return 0;
    */
  }

  u8 SpoilerData_GetIsItemLocationRevealed(u16 itemIndex) {
    if (gSettingsContext.ingameSpoilers) {
      return 1;
    }

    SpoilerItemLocation* itemLoc = SpoilerData_ItemLoc(itemIndex);

    if (itemLoc->RevealType == REVEALTYPE_ALWAYS) {
      return 1;
    } else if (itemLoc->RevealType == REVEALTYPE_NORMAL) {
      return 0;
    }

    return SaveFile_GetIsSceneDiscovered(itemLoc->LocationScene);
  }

}  // namespace rnd