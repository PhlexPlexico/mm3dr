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
#include "rnd/input.h"
#include "rnd/item_override.h"
#include "rnd/link.h"
#include "rnd/rheap.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include "z3d/z3DVec.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
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
    // SaveFile_LoadExtSaveData(1);
    //  TODO: Maybe make this an option?
    link::FixSpeedIssues();
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
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
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
  static bool titlePlayed = false;
#endif
  void calc(game::State* state) {
    Context& context = GetContext();
    context.gctx = nullptr;

    if (!context.has_initialised && state->type == game::StateType::FirstGame) {
      Init(context);
    }

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    if (state->type == game::StateType::FileSelect) {
      if (!titlePlayed) {
        game::sound::ControlStream(game::sound::StreamPlayer::DEFAULT_PLAYER, 1, 1);
        game::sound::PlayStream(game::sound::StreamId::NA_BGM_MUJURA_2, game::sound::StreamPlayer::DEFAULT_PLAYER);
        titlePlayed = true;
      }

      return;
    } else if (state->type != game::StateType::Play)
      return;
#else
    if (state->type != game::StateType::Play)
      return;
#endif

    context.gctx = static_cast<game::GlobalContext*>(state);
    Input_Update();
    if (context.gctx->GetPlayerActor()) {
      ItemOverride_Update();
      link::HandleFastOcarina(context.gctx);
      link::HandleFastArrowSwitch(context.gctx->GetPlayerActor());
      link::FixFreeCameraReset();
      // May need this for further button presses and checks if we're swimming or not.
      if (context.gctx->GetPlayerActor()->flags1.IsSet(game::act::Player::Flag1::InWater) &&
          !context.gctx->GetPlayerActor()->flags_94.IsSet(game::act::Actor::Flag94::Grounded)) {
        context.is_swimming = true;
      } else {
        context.is_swimming = false;
      }
    }

    return;
  }

  void readPadInput() {
    auto* gctx = GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return;

    const u32 pressedButtons = gctx->pad_state.input.buttons.flags;
    const u32 newButtons = gctx->pad_state.input.new_buttons.flags;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    auto* saveData = GetContext().gctx->GetPlayerActor();
    if (newButtons == (u32)game::pad::Button::ZR)
      rnd::util::Print("%s: Player held item is %#04x\n", __func__, saveData->held_item);
#endif
    if (gSettingsContext.customMaskButton != 0 && pressedButtons == gSettingsContext.customMaskButton) {
      game::ui::OpenScreen(game::ui::ScreenType::Masks);
    } else if (gSettingsContext.customItemButton != 0 && pressedButtons == gSettingsContext.customItemButton) {
      game::ui::OpenScreen(game::ui::ScreenType::Items);
    } else if (gSettingsContext.customNotebookButton != 0 && pressedButtons == gSettingsContext.customNotebookButton) {
      if (game::GetCommonData().save.inventory.collect_register.bombers_notebook != 0)
        game::ui::OpenScreen(game::ui::ScreenType::Schedule);
      else
        game::ui::OpenScreen(game::ui::ScreenType::Items);
    } else if (gSettingsContext.customMapButton != 0 && pressedButtons == gSettingsContext.customMapButton) {
      // Clear map screen type. (Needed because the screen could be in "soaring" mode.)
      util::Write<u8>(game::ui::GetScreen(game::ui::ScreenType::Map), 0x78E, 0);
      game::ui::OpenScreen(game::ui::ScreenType::Map);
      gctx->pad_state.input.buttons.Clear(game::pad::Button::Select);
      gctx->pad_state.input.new_buttons.Clear(game::pad::Button::Select);
    } else if ((gSettingsContext.customIngameSpoilerButton != 4 && newButtons == (u32)game::pad::Button::Select) ||
               (gSettingsContext.customIngameSpoilerButton != 8 && newButtons == (u32)game::pad::Button::Start)) {
      if (game::GetCommonData().save.inventory.collect_register.bombers_notebook != 0)
        game::ui::OpenScreen(game::ui::ScreenType::Schedule);
      else
        game::ui::OpenScreen(game::ui::ScreenType::Items);
    }
    return;
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