#ifndef _RND_LINK_
#define _RND_LINK_

#include "common/advanced_context.h"
#include "game/common_data.h"
#include "game/pad.h"
#include "game/ui.h"
#include "game/ui/layouts/play_hud.h"

namespace rnd::link {
  void FixSpeedIssues();
  void HandleFastOcarina(game::GlobalContext*);
  
}  // namespace rnd::link

#endif