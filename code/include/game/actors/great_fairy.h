#ifndef _GAME_ACTORS_GREAT_FAIRY
#define _GAME_ACTORS_GREAT_FAIRY

#include "game/actor.h"
#include "game/as.h"
#include "game/collision.h"

namespace game::act {

  struct GreatFairy : Actor {
    void* calc_fn;
    as::ActorUtil actor_util;
    int field_288;
    u8 gap_28C[1400];
    int field_804;
    u8 gap_808[1272];
    u16 field_D00;
    u8 gap_D02[138];
    Actor* beam_actor;
    double field_D90;
    u8 gap_D98[6];
    u16 field_D9E;
    u16 field_DA0;
    u16 field_DA2;
    u16 countdown;
    u8 gap_DA6[2];
    int field_DA8;
    u8 gap_DAC[1276];
    int field_12A8;
    u16 field_12AC;
    u8 gap_12AE[2];
    int field_12B0;
  };
  static_assert(offsetof(GreatFairy, calc_fn) == 0x1F8);
  static_assert(sizeof(GreatFairy) == 0x12b8);

}  // namespace game::act

#endif  // _GAME_ACTORS_GREAT_FAIRY