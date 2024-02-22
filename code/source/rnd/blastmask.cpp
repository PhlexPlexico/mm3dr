#include "rnd/blastmask.h"

namespace rnd {
  extern "C" {
  u8 checkBlastMaskCooldown() {
    return gSettingsContext.blastMaskCooldown;
  }
  }
}  // namespace rnd