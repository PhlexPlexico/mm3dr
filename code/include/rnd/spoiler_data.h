#ifndef _RND_SPOILER_DATA_H_
#define _RND_SPOILER_DATA_H_

#include "z3d/z3DVec.h"

#define SPOILER_SPHERES_MAX 50
#define SPOILER_ITEMS_MAX 512
#define SPOILER_STRING_DATA_SIZE 16384

namespace rnd {
  typedef enum {
    SPOILER_CHK_NONE,
    SPOILER_CHK_ALWAYS_COLLECTED,
    SPOILER_CHK_CHEST,
    SPOILER_CHK_COLLECTABLE,
    SPOILER_CHK_SWAMP_SKULLTULA,
    SPOILER_CHK_OCEAN_SKULLTULA,
    SPOILER_CHK_ITEM_GET_INF,
    SPOILER_CHK_EVENT_CHK_INF,
    SPOILER_CHK_INF_TABLE,
    SPOILER_CHK_COW,
    SPOILER_CHK_MINIGAME,
    SPOILER_CHK_SCRUB,
    SPOILER_CHK_SHOP_ITEM,
    SPOILER_CHK_MAGIC_BEANS,
  } SpoilerCollectionCheckType;

  // Location groups for checks, used to group the checks by logical location
  typedef enum {
    GROUP_NO_GROUP,
    GROUP_STARTING_ITEM,
    GROUP_DEKU_PALACE,
    GROUP_EAST_CLOCK_TOWN,
    GROUP_DUNGEON_WOODFALL_TEMPLE,
    GROUP_DUNGEON_SNOWHEAD_TEMPLE,
    GROUP_E_CLOCK_TOWN,
    GROUP_GORON_VILLAGE,
    GROUP_GREAT_BAY_COAST,
    GROUP_IKANA_CANYON,
    GROUP_IKANA_GRAVEYARD,
    GROUP_LAUNDRY_POOL,
    GROUP_MILK_ROAD,
    GROUP_MOUNTAIN_VILLAGE,
    GROUP_N_CLOCK_TOWN,
    GROUP_PATH_SNOWHEAD,
    GROUP_PINNACLE_ROCK,
    GROUP_ROAD_IKANA,
    GROUP_ROAD_SWAMP,
    GROUP_ROMANI_RANCH,
    GROUP_S_CLOCK_TOWN,
    GROUP_SNOWHEAD,
    GROUP_SOUTHERN_SWAMP,
    GROUP_STOCKPOTINN,
    GROUP_STONE_TOWER,
    GROUP_TERMINA_FIELD,
    GROUP_TWIN_ISLANDS,
    GROUP_W_CLOCK_TOWN,
    GROUP_WOODFALL,
    GROUP_ZORA_CAPE,
    GROUP_ZORA_HALL,
    GROUP_DUNGEON_GREAT_BAY,
    GROUP_DUNGEON_STONE_TOWER,
    GROUP_DUNGEON_PIRATE_FORTRESS,
    GROUP_DUNGEON_BENEATH_THE_WELL,
    GROUP_DUNGEON_IKANA_CASTLE,
    GROUP_DUNGEON_SECRET_SHRINE,
    GROUP_DUNGEON_THE_MOON,
    GROUP_SWAMP_SKULLTULA_HOUSE,
    GROUP_OCEAN_SKULLTULA_HOUSE,

    SPOILER_COLLECTION_GROUP_COUNT,
    // XXX: Not sure about this comment, different for mm3d?
    // Grottos are all 0x3E
  } SpoilerCollectionCheckGroup;

  typedef struct {
    u16 LocationStrOffset;
    u16 ItemStrOffset;
    SpoilerCollectionCheckType CollectionCheckType;
    u8 LocationScene;
    u8 LocationFlag;
    SpoilerCollectionCheckGroup Group;
  } SpoilerItemLocation;

  typedef struct {
    u8 ItemCount;
    u16 ItemLocationsOffset;
  } SpoilerSphere;

  typedef struct {
    u8 SphereCount;
    u16 ItemLocationsCount;
    SpoilerSphere Spheres[SPOILER_SPHERES_MAX];
    SpoilerItemLocation ItemLocations[SPOILER_ITEMS_MAX];
    u16 SphereItemLocations[SPOILER_ITEMS_MAX];
    char StringData[SPOILER_STRING_DATA_SIZE];
    u16 GroupItemCounts[SPOILER_COLLECTION_GROUP_COUNT];
    u16 GroupOffsets[SPOILER_COLLECTION_GROUP_COUNT];
  } SpoilerData;

  extern "C" SpoilerData gSpoilerData;

  char* SpoilerData_GetItemLocationString(u16 itemIndex);
  char* SpoilerData_GetItemNameString(u16 itemIndex);
  SpoilerItemLocation GetSpoilerItemLocation(u8 sphere, u16 itemIndex);
  u8 SpoilerData_GetIsItemLocationCollected(u16 itemIndex);
  u8 SpoilerData_ChestCheck(SpoilerItemLocation itemLoc);
  u8 SpoilerData_CollectableCheck(SpoilerItemLocation itemLoc);
  u8 SpoilerData_ItemGetInfCheck(u8 slot);
  u8 SpoilerData_InfTableCheck(u8 offset, u8 bit);
  u8 SpoilerData_UpgradeCheck(u8 bit);
  u8 SpoilerData_CowCheck(SpoilerItemLocation itemLoc);
  u8 SpoilerData_FishingCheck(SpoilerItemLocation itemLoc);
  u8 SpoilerData_ScrubCheck(SpoilerItemLocation itemLoc);
  u8 SpoilerData_ShopItemCheck(SpoilerItemLocation itemLoc);
  u8 SpoilerData_MagicBeansCheck(SpoilerItemLocation itemLoc);
}  // namespace rnd

#endif  // _RND_SPOILER_DATA_H_