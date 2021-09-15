#pragma once

#include "z3d/z3DVec.h"
#include <stdbool.h>
// namespace game {
// struct GlobalContext;
// }


typedef struct {
  //GlobalContext* gctx;
  bool has_initialised;

  bool going_back_in_time;

  bool use_fast_swim;
  u32 a_press_duration;
} Context;

Context *GetContext();
void InitContext(Context*);