#ifndef _RND_BOSS_H_
#define _RND_BOSS_H_
#include "common/advanced_context.h"
#include "game/actors/boss/twinmold.h"
#include "rnd/settings.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <optional>
#include <type_traits>
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  void FixBosses();
  extern "C" {
    u8 IsTwinmoldSetToRestoration();
  }
} // namespace rnd 

#endif