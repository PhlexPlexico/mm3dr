#include "common/advanced_context.h"
#include "game/actorresource.h"
#include "game/common_data.h"
#include "game/context.h"
#include "game/message.h"
#include "game/sound.h"
#include "game/states/state.h"
#include "game/ui.h"
#include "rnd/extdata.h"
#include "rnd/icetrap.h"
#include "rnd/item_override.h"
#include "rnd/link.h"
#include "rnd/rheap.h"
#include "rnd/savefile.h"
#include "z3d/z3DVec.h"

#ifdef ENABLE_DEBUG
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace rnd {
  void Init(Context& context) {
    // XXX: Temp switch to ensure patch is running.

    rHeap_Init();
    ItemOverride_Init();
    extDataInit();
    SaveFile_LoadExtSaveData(1);
    // TODO: Maybe make this an option?
    link::FixSpeedIssues();
#ifdef ENABLE_DEBUG
    util::Print("MM3DR Initialized (" __DATE__ " " __TIME__ ")\n");
    game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_CHAT_ALLERT);
#else
    game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_CLEAR1);
#endif
    context.has_initialised = true;
  }
  extern "C" {
  void* __service_ptr = nullptr;
  char* fake_heap_start;
  char* fake_heap_end;
  extern void (*__init_array_start[])(void) __attribute__((weak));
  extern void (*__init_array_end[])(void) __attribute__((weak));
  void calc(game::State* state) {
    Context& context = GetContext();
    context.gctx = nullptr;

    if (!context.has_initialised && state->type == game::StateType::FirstGame)
      Init(context);
    if (state->type != game::StateType::Play)
      return;
    context.gctx = static_cast<game::GlobalContext*>(state);

    if (context.gctx->GetPlayerActor())
      ItemOverride_Update();

#ifdef ENABLE_DEBUG
    if (context.gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZL)) {
      game::act::Player* link = context.gctx->GetPlayerActor();
      // Before calling let's be absolutely sure we have the player available.
      if (link) {
        game::SaveData& saveCtx = game::GetCommonData().save;
        for (int i = 0; i < 24; i++) {
          rnd::util::Print("%s: Mask %i is %u\n", __func__, i, saveCtx.inventory.masks[i]);
        }

        return;
      }
    }
#endif

    return;
  }
  void readPadInput() {
    auto* gctx = GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return;

    const bool zr = gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZR);
    const bool start = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Start);
    const bool select = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Select);
    if (!zr && select) {
      game::ui::OpenScreen(game::ui::ScreenType::Masks);
      return;
    }

    if (start && !zr) {
      game::ui::OpenScreen(game::ui::ScreenType::Items);
      return;
    }

    if (zr && start) {
      if (game::GetCommonData().save.inventory.collect_register.bombers_notebook != 0)
        game::ui::OpenScreen(game::ui::ScreenType::Schedule);
      else
        game::ui::OpenScreen(game::ui::ScreenType::Items);
      return;
    }

    if (zr && select) {
      // Clear map screen type. (Needed because the screen could be in "soaring" mode.)
      util::Write<u8>(game::ui::GetScreen(game::ui::ScreenType::Map), 0x78E, 0);
      game::ui::OpenScreen(game::ui::ScreenType::Map);
      gctx->pad_state.input.buttons.Clear(game::pad::Button::Select);
      gctx->pad_state.input.new_buttons.Clear(game::pad::Button::Select);
      return;
    }
  }
  void _start(void) {
    // Just in case something needs to be dynamically allocated...
    static char s_fake_heap[0x80000];

    fake_heap_start = &s_fake_heap[0];
    fake_heap_end = &s_fake_heap[sizeof(s_fake_heap)];
    for (size_t i = 0; i < size_t(__init_array_end - __init_array_start); i++) {
      __init_array_start[i]();
    }
  }
  }

}  // namespace rnd