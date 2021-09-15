#include "z3d/z3DVec.h"
#include <stdbool.h>

//struct GlobalContext;

struct Context {
  //GlobalContext* gctx;
  bool has_initialised;

  bool going_back_in_time;

  bool use_fast_swim;
  u32 a_press_duration;
};

Context& GetContext();
