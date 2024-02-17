#ifndef _RND_CUSTOM_SCREEN_H_
#define _RND_CUSTOM_SCREEN_H_

#include "common/advanced_context.h"
#include "common/types.h"
#include "game/ui/screens/gearscreen.h"
#include "rnd/savefile.h"
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  namespace gearscreen {
    extern "C" void GearScreen_GetStoredTradeItem(game::ui::screens::GearScreen*);
    void GearScreen_DrawAndShowItem(game::ItemId, game::ui::Anim*, u16, int);
    bool GearScreen_LoopTradeItemsForward(game::ui::Anim*, int, game::ItemId, game::ItemId, int);
    bool GearScreen_LoopTradeItemsBackward(game::ui::Anim*, int, game::ItemId, game::ItemId, int);
    int GearScreen_GetTextIdFromItemId(game::ItemId);
    int GearScreen_GetModelIdFromItemId(game::ItemId);
  }  // namespace gearscreen
}  // namespace rnd

#endif