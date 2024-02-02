#ifndef _RND_CUSTOM_MESSAGES_H_
#define _RND_CUSTOM_MESSAGES_H_

#include "common/advanced_context.h"
#include "game/common_data.h"
#include "game/sound.h"
#include "rnd/settings.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  extern "C" {
  bool SceneEntranceOverride();
  void ForceTempleFlags();
  }
}  // namespace rnd

#endif