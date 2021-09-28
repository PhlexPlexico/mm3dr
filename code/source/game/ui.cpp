#include "game/ui.h"

#include <string_view>

#include "common/advanced_context.h"
#include "common/utils.h"
#include "game/context.h"
#include "game/static_context.h"
#include "game/ui/screens/screen.h"

namespace game::ui {

ScreenContext& GetScreenContext() {
  return *rnd::util::GetPointer<ScreenContext>(0x72F5BC);
}

Screen* GetScreen(ScreenType screen) {
  switch (screen) {
  case ScreenType::Black:
    return *rnd::util::GetPointer<Screen*>(0x656B00);
  case ScreenType::Main:
    return *rnd::util::GetPointer<Screen*>(0x656B04);
  case ScreenType::Schedule:
    return *rnd::util::GetPointer<Screen*>(0x656b08);
  case ScreenType::Quest:
    return *rnd::util::GetPointer<Screen*>(0x656B0C);
  case ScreenType::Items:
    return *rnd::util::GetPointer<Screen*>(0x656B10);
  case ScreenType::Map:
    return *rnd::util::GetPointer<Screen*>(0x656B14);
  case ScreenType::Masks:
    return *rnd::util::GetPointer<Screen*>(0x656B18);
  case ScreenType::Ocarina:
    return *rnd::util::GetPointer<Screen*>(0x656B1C);
  }
  return nullptr;  // should be unreachable
}

bool OpenScreen(ScreenType screen) {
  GlobalContext* gctx = rnd::GetContext().gctx;
  ScreenContext& ui_ctx = GetScreenContext();

  if (!gctx || gctx->type != StateType::Play)
    return false;

  ui_ctx.new_screen = GetScreen(screen);
  gctx->pause_flags = PauseFlag::PauseCalc;
  gctx->enable_letterbox = false;

  if (GetStaticContext().field_D38) {
    GetStaticContext().field_D38 = 0;
    gctx->field_CAB0 = 0xA0A0A000;
  }
  if (!gctx->field_CAAD)
    gctx->field_CAB0 = 0;

  if (gctx->some_fn2 && !gctx->some_fn2(&gctx->some_ptr) && gctx->some_fn1)
    gctx->some_fn1(&gctx->some_ptr, 0);

  return true;
}

}  // namespace game::ui
