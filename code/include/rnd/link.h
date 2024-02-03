#ifndef _RND_LINK_
#define _RND_LINK_

#include <optional>
#include "common/advanced_context.h"
#include "game/common_data.h"
#include "game/pad.h"
#include "game/ui.h"
#include "game/ui/layouts/play_hud.h"
#include "rnd/settings.h"

namespace rnd::link {
  void FixSpeedIssues();
  void HandleFastOcarina(game::GlobalContext*);
  void HandleFastArrowSwitch(game::act::Player*);
  void FixFreeCameraReset();

}  // namespace rnd::link

#endif