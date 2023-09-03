#include "rnd/settings.h"
#include "rnd/spoiler_data.h"
#include "rnd/savefile.h"
//#include "../include/draw.h"

extern "C" {
    #include <3ds/svc.h>
}
#include <string.h>

namespace rnd {
typedef struct {
    u16 spoilerIndex;
    u8 keyAmount;
} KeyData;

typedef enum {
    DUNGEON_WOODFALL = 0,
    DUNGEON_SNOWHEAD,
    DUNGEON_GREAT_BAY,
    DUNGEON_STONE_TOWER,
    DUNGEON_PIRATE_FORTRESS,
    DUNGEON_BENEATH_THE_WELL,
    DUNGEON_IKANA_CASTLE,
    DUNGEON_SECRET_SHRINE,
    DUNGEON_THE_MOON,
    DUNGEON_SWAMP_SKULLTULA_HOUSE,
    DUNGEON_OCEAN_SKULLTULA_HOUSE,
} DungeonId;

static u8 keyFinderInit = 0;
static KeyData keyData[DUNGEON_STONE_TOWER + 1][10];

const char* spoilerCollectionGroupNames[] = {
    "All Item Locations", 
    "Deku Palace",
    "Woodfall Temple",
    "Snowhead Temple",
    "East Clock Town",
    "Goron Village",
    "Great Bay Coast",
    "Ikana Canyon",
    "Ikana Graveyard",
    "Laundry Pool",
    "Milk Road",
    "Mountain Village",
    "North Clock Town",
    "Path to Snowhead",
    "Pinnacle Rock",
    "Road to Ikana",
    "Road to Southern Swamp",
    "Romani Ranch",
    "South Clock Town",
    "Snowhead",
    "Southern Swamp",
    "StockPotInn",
    "Stone Tower",
    "Termina Field",
    "Twin Islands",
    "West Clock Town",
    "Woodfall",
    "Zora Cape",
    "Zora Hall",
    "Greay Bay Temple",
    "Stone Tower Temple",
    "Pirate Fortress",
    "Beneath the Well",
    "Ikana Castle",
    "Secret Shrine",
    "The Moon",
    "Swamp Skulltula House",
    "Ocean Skulltula House",
};

static s8 spoilerGroupDungeonIds[] = {
    -1,
    -1,
    GROUP_DUNGEON_WOODFALL_TEMPLE,
    GROUP_DUNGEON_SNOWHEAD_TEMPLE,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    GROUP_DUNGEON_GREAT_BAY,
    GROUP_DUNGEON_STONE_TOWER,
    GROUP_DUNGEON_PIRATE_FORTRESS,
    GROUP_DUNGEON_BENEATH_THE_WELL,
    GROUP_DUNGEON_IKANA_CASTLE,
    GROUP_DUNGEON_SECRET_SHRINE,
    GROUP_DUNGEON_THE_MOON,
    GROUP_SWAMP_SKULLTULA_HOUSE,
    GROUP_OCEAN_SKULLTULA_HOUSE,
};

const char* spoilerEntranceGroupNames[] = {
    "Randomized Entrances",
    "Spawns/Warps", "Clock Town", "Termina Field", "Southern Swamp",
    "Snowhead", "Great Bay", "Ikana", "Milk Road",
    "The Moon",
};

const char* DungeonNames[] = {
    "Woodfall Temple",
    "Snowhead Temple",
    "Great Bay Temple",
    "Stone Tower Temple",
    "Pirate's Fortress",
    "Beneath The Well",
    "Ikana Castle",
    "Secret Shrine",
    "The Moon",
    "Swamp Skulltula House",
    "Ocean Skulltula House",
};

static const char* const smallKeyStringWoodfall  = "Woodfall Temple Small Key";
static const char* const smallKeyStringSnowhead  = "Snowhead Temple Small Key";
static const char* const smallKeyStringGreatBay  = "Great Bay Temple Small Key";
static const char* const smallKeyStringStone     = "Stone Tower Temple Small Key";

static const char* const keyRingStringWoodfall  = "Woodfall Temple Key Ring";
static const char* const keyRingStringSnowhead  = "Snowhead Temple Key Ring";
static const char* const keyRingStringGreatBay  = "Great Bay Temple Key Ring";
static const char* const keyRingStringStone     = "Stone Tower Temple Key Ring";

#define WOODFALL_KEY_COUNT 1
#define SNOWHEAD_KEY_COUNT 3
#define GREAT_KEY_COUNT 1
#define STONE_KEY_COUNT 4

// Used to compare key strings and item string of spoiler data.
// The regular strcmp won't be enough since items in shops have a colon and price added after.
static u8 strcmp_key(char* str, const char* keyStr) {
    for (size_t i = 0; i <= strlen(keyStr); i++) {
        if (keyStr[i] == '\0' && (str[i] == '\0' || str[i] == ':')) {
            return 1;
        }
        if (keyStr[i] != str[i]) {
            return 0;
        }
    }
    return 0;
}

static const char* GetKeyName(DungeonId id, u8 keyRing) {
    static const char* noStr = "";

    switch (id) {
        case DUNGEON_WOODFALL:
            return keyRing ?  keyRingStringWoodfall : smallKeyStringWoodfall;
        case DUNGEON_SNOWHEAD:
            return keyRing ? keyRingStringSnowhead : smallKeyStringSnowhead;
        case DUNGEON_GREAT_BAY:
            return keyRing ? keyRingStringGreatBay : smallKeyStringGreatBay;
        case DUNGEON_STONE_TOWER:
            return keyRing ? keyRingStringStone : smallKeyStringStone;
        default:
            return noStr;
    }
}

u8 Dungeon_KeyAmount(u32 id) {
    switch (id) {
        case DUNGEON_WOODFALL:
            return WOODFALL_KEY_COUNT;
        case DUNGEON_SNOWHEAD:
            return SNOWHEAD_KEY_COUNT;
        case DUNGEON_GREAT_BAY:
            return GREAT_KEY_COUNT;
        case DUNGEON_STONE_TOWER:
            return STONE_KEY_COUNT;
        default:
            return 0;
    }
}

// Stores the indexes of the gSpoilerData where small keys and key rings are for faster lookup.
static void InitKeyFinder(void) {
    if (keyFinderInit) {
        return;
    }
    keyFinderInit = 1;

    for (size_t i = 0; i < ARR_SIZE(keyData); i++) {
        for (size_t j = 0; j < ARR_SIZE(keyData[0]); j++) {
            keyData[i][j].spoilerIndex = -1;
        }
    }

    u8 keyDataIndex[DUNGEON_STONE_TOWER + 1] = { 0 };

    for (size_t item = 0; item < gSpoilerData.ItemLocationsCount; item++) {
        for (u32 dungeonId = DUNGEON_WOODFALL; dungeonId <= DUNGEON_STONE_TOWER; dungeonId++) {
            if (dungeonId == DUNGEON_PIRATE_FORTRESS || dungeonId == DUNGEON_BENEATH_THE_WELL ||
                dungeonId == DUNGEON_IKANA_CASTLE || dungeonId == DUNGEON_SECRET_SHRINE || 
                dungeonId == DUNGEON_THE_MOON || dungeonId == DUNGEON_SWAMP_SKULLTULA_HOUSE || 
                dungeonId == DUNGEON_OCEAN_SKULLTULA_HOUSE) {
                continue;
            }
            if (strcmp_key(SpoilerData_GetItemNameString(item), GetKeyName(DungeonId(dungeonId), 0))) {
                keyData[dungeonId][keyDataIndex[dungeonId]].spoilerIndex = item;
                keyData[dungeonId][keyDataIndex[dungeonId]].keyAmount    = 1;
                keyDataIndex[dungeonId]++;
                break;
            } else if (strcmp_key(SpoilerData_GetItemNameString(item), GetKeyName(DungeonId(dungeonId), 1))) {
                keyData[dungeonId][keyDataIndex[dungeonId]].spoilerIndex = item;
                keyData[dungeonId][keyDataIndex[dungeonId]].keyAmount    = Dungeon_KeyAmount(dungeonId);
                keyDataIndex[dungeonId]++;
                break;
            }
        }
    }
}

u8 Dungeon_FoundSmallKeys(u32 id) {
    if (!keyFinderInit) {
        InitKeyFinder();
    }

    u8 amount = 0;
    for (size_t i = 0; i < ARR_SIZE(keyData[id]); i++) {
        if (keyData[id][i].spoilerIndex == -1) {
            break;
        }
        if (SpoilerData_GetIsItemLocationCollected(keyData[id][i].spoilerIndex)) {
            amount += keyData[id][i].keyAmount;
        }
    }
    return amount;
}
}