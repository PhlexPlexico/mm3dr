#ifndef _RND_CHEST_H_
#define _RND_CHEST_H_

#include "common/advanced_context.h"
#include "rnd/settings.h"
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif
namespace rnd {
  extern "C" u8 checkBlastMaskCooldown();
}  // namespace rnd
#endif