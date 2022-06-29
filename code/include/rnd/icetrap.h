#ifndef _RND_ICETRAP_H
#define _RND_ICETRAP_H

#include "common/advanced_context.h"
#include "game/common_data.h"
#include "game/player.h"

namespace rnd {
  void IceTrap_Push();
  void IceTrap_Give();
  bool IceTrap_IsPending();
}  // namespace rnd

#endif  // ICETRAP_H