#ifndef _GAME_SKELANIME_H
#define _GAME_SKELANIME_H

#include "common/types.h"
#include "game/context.h"
#include "z3d/z3DVec.h"

namespace game {

  struct SkelAnime {
    u8 limb_count;
    u8 mode;
    u8 d_list_count;
    s8 taper;
    void** skeleton; /*  An array of pointers to limbs. Can be StandardLimb, LodLimb, or SkinLimb. */
    void* animation; /* Can be an AnimationHeader or PlayerAnimationHeader. */
    float start_frame;
    float end_frame;
    float animation_length;
    float cur_frame;
    float play_speed;
    z3dVec3s* joint_table;
    z3dVec3s* morph_table;
    float morph_weight;
    float morph_rate;
    union {
      s32 (*normal)(struct SkelAnime*);  // Can be Loop, Partial loop, Play once, Morph, or Tapered morph
      s32 (*player)(struct game::GlobalContext*, struct SkelAnime*);  // Loop, Play once, and Morph
    } update;
    s8 init_flags;
    u8 move_flags;
    s16 prev_yaw;
    z3dVec3s prev_transl;
    z3dVec3s base_transl;
  };

}  // namespace game

#endif