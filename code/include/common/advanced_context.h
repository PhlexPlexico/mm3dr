#ifndef _COMMON_ADVANCED_CONTEXT_H
#define _COMMON_ADVANCED_CONTEXT_H
#include "z3d/z3DVec.h"
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
extern "C" {
#include <3ds/svc.h>
}
#endif
namespace game {
  struct GlobalContext;
}

namespace rnd {

  struct Context {
    game::GlobalContext* gctx;
    bool has_initialised = false;

    bool going_back_in_time = false;

    bool use_fast_swim = true;
    u32 a_press_duration = 0;
  };

  Context& GetContext();

}  // namespace rnd
#endif