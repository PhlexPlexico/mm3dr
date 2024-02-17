#ifndef _GAME_ACTORS_CHEST_H
#define _GAME_ACTORS_CHEST_H

#include "game/actor.h"
#include "game/as.h"
#include "game/collision.h"
#include "game/skelanime.h"
#include "rnd/item_override.h"

namespace game::actors {
  enum class EnBoxType : u8 {
    ENBOX_TYPE_BIG = 0,  // E.g. Hookshot Chest
    ENBOX_TYPE_BIG_ROOM_CLEAR = 1,
    ENBOX_TYPE_BIG_ORNATE = 2,  // E.g. Boss Key Chests
    ENBOX_TYPE_BIG_SWITCH_FLAG_FALL = 3,
    ENBOX_TYPE_BIG_INVISIBLE = 4,
    ENBOX_TYPE_SMALL = 5,
    ENBOX_TYPE_SMALL_INVISIBLE = 6,
    ENBOX_TYPE_SMALL_ROOM_CLEAR = 7,
    ENBOX_TYPE_SMALL_SWITCH_FLAG_FALL = 8,
    ENBOX_TYPE_BIG_SONG_ZELDAS_LULLABY = 9,
    ENBOX_TYPE_BIG_SONG_SUNS = 10,
    ENBOX_TYPE_BIG_SWITCH_FLAG = 11,
    ENBOX_TYPE_SMALL_SWITCH_FLAG = 12
  };

  struct En_Box {
    game::act::DynaPolyActor dyna;
    SkelAnime* skel_anime;
    u8 gap_210[52];
    CollisionInfoCylinder* collision_cylinder;
    u8 gap_248[84];
    int field_29C;
    u8 gap_2A0[8];
    void* some_fn;
    u8 gap_2AC[312];
    u16 some_item_check;
    u8 movement_flags;
    u8 alpha;
    u8 switch_flag;
    EnBoxType chest_type;
    u8 iceSmokeTImer;
    s8 field_3EB;
    u8 gap_3EC[16];
    void* field_3fc;
    u8 gap_400[16];
    game::act::Actor* field_410;
    int csId2;
    rnd::GetItemID GetItemID;
    s32 collectableFlag;
    u8 gap_420[8];
  };
}  // namespace game::actors

#endif