#ifndef _RND_DUNGEON_H
#define _RND_DUNGEON_H

#include <string.h>
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include "rnd/spoiler_data.h"
//#include "rnd/draw.h"
extern "C" {
#include <3ds/svc.h>
}

#define WOODFALL_KEY_COUNT 1
#define SNOWHEAD_KEY_COUNT 3
#define GREAT_KEY_COUNT 1
#define STONE_KEY_COUNT 4

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

  extern const char DungeonNames[][25];

  static const char* const smallKeyStringWoodfall = "Woodfall Temple Small Key";
  static const char* const smallKeyStringSnowhead = "Snowhead Temple Small Key";
  static const char* const smallKeyStringGreatBay = "Great Bay Temple Small Key";
  static const char* const smallKeyStringStone = "Stone Tower Temple Small Key";

  static const char* const keyRingStringWoodfall = "Woodfall Temple Key Ring";
  static const char* const keyRingStringSnowhead = "Snowhead Temple Key Ring";
  static const char* const keyRingStringGreatBay = "Great Bay Temple Key Ring";
  static const char* const keyRingStringStone = "Stone Tower Temple Key Ring";

  u8 Dungeon_KeyAmount(u32);
  u8 Dungeon_FoundSmallKeys(u32);

}  // namespace rnd

#endif