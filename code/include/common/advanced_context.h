/**
 * @file advanced_context.h
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries (context.h). Edited to adjust for the randomizer.
 */
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

    bool is_swimming = false;
    bool use_fast_swim = true;
    u32 a_press_duration = 0;
  };

  Context& GetContext();

}  // namespace rnd
#endif