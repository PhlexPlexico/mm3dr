#include "common/context.h"
#include "common/debug.h"
#include "common/hidstate.h"
#include "common/types.h"
#include "common/utils.h"
#include "game/camera.h"
#include "game/common_data.h"
#include "game/context.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/player.h"
#include "game/sound.h"
#include "game/states/state.h"
#include "game/ui.h"
#include "game/ui/screens/gear_screen.h"
#include "game/ui/screens/schedule_screen.h"


namespace rnd {

advance_input_t inputs = {};
bool frameBufferInit = true;
bool showTitle = true;

namespace {

void Init(Context& context) {
  util::Print("Majora's Mask 3D Randomizer initialised (" __DATE__ " " __TIME__ ")");
  game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_PREDEMO_OMEN);
  context.has_initialised = true;
}

}  // anonymous namespace

[[maybe_unused]] static void PrintDebug(game::GlobalContext* gctx) {
  std::string actors_str = "actors:";
  for (size_t i = 0; i < gctx->actors.lists.size(); ++i) {
    game::ActorList& list = gctx->actors.lists[i];
    actors_str += util::StringFromFormat("\ntype %02zu: ", i);
    for (auto* actor = list.first; actor; actor = actor->next) {
      actors_str += util::StringFromFormat("%04x[%04x] ", u16(actor->id), actor->params);
    }
  }
  util::Print(actors_str);

  const auto* player = gctx->GetPlayerActor();
  if (player) {
    util::Print("%08lx %08lx %08lx %08lx %08x", player->flags1.flags, player->flags2.flags,
                player->flags3.flags, player->flags4, player->flags_94.flags);

    util::Print("state handler: %p - 92C: %u - 92D: %u", player->state_handler_fn, player->fn1_idx,
                player->fn2_idx);

    auto* camera = &gctx->main_camera + gctx->camera_idx;
    util::Print("camera_idx=%u target=%p%s state=%04x mode=%04x", gctx->camera_idx,
                camera->target_actor,
                (camera->target_actor && camera->target_actor == player) ? "(player)" : "",
                u16(camera->state), u16(camera->mode));
  }
}

static bool IsStartOrSelectPressed() {
  return GetContext().gctx && GetContext().gctx->pad_state.input.new_buttons.IsOneSet(
                                  game::pad::Button::Start, game::pad::Button::Select);
}

static void UiOcarinaScreenUpdate() {
  if (!game::ui::CheckCurrentScreen(game::ui::ScreenType::Ocarina))
    return;
  auto* screen = game::ui::GetScreen(game::ui::ScreenType::Ocarina);

  if (IsStartOrSelectPressed()) {
    util::Write<bool>(screen, 0x41, true);  // is transitioning
    auto* layout_ocarina = util::BitCastPtr<game::ui::Layout*>(screen, 0x10);
    auto* layout_music_list = util::BitCastPtr<game::ui::Layout*>(screen, 0x14);
    const bool is_menu_ocarina = util::BitCastPtr<bool>(screen, 0x40);
    if (is_menu_ocarina)
      util::GetPointer<void(void*)>(0x5F54DC)(layout_ocarina);
    else
      util::GetPointer<void(void*)>(0x5F7DC8)(layout_music_list);
    game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_DECIDE);
  }
}

void scan_shared_hid_inputs() {
  inputs.cur.val = shared_hid->pad.pads[shared_hid->pad.index].curr.val;
  inputs.pressed.val = (inputs.cur.val) & (~inputs.old.val);
  inputs.up.val = (~inputs.cur.val) & (inputs.old.val);
  inputs.old.val = inputs.cur.val;
}

// Main entry hook in game loop.
RST_HOOK void Calc(game::State* state) {
  Context& context = GetContext();
  context.gctx = nullptr;

  if (!context.has_initialised && state->type == game::StateType::FirstGame)
    Init(context);

  context.gctx = static_cast<game::GlobalContext*>(state);
  // Move in improvements from Project Restoration
  // UiOcarinaScreenUpdate();
  // End improvments.
  scan_shared_hid_inputs();
}

RST_HOOK void DrawMenu() {

}

RST_HOOK void PreActorCalcHook() {
  // FixOwlStatueActivationTrigger();
}

// RST_HOOK void PostActorCalcHook() {
//   //FixBosses();
// }

// This opens menu based on what buttons are pressed.
RST_HOOK void UiScheduleTriggerHook() {
  auto* gctx = GetContext().gctx;
  if (!gctx || gctx->type != game::StateType::Play)
    return;

  const bool zr = gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZR);
  const bool start = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Start);
  const bool select = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Select);
  if (!zr && select)
    game::ui::OpenScreen(game::ui::ScreenType::Items);
  if (!zr && start && game::GetCommonData().save.inventory.collect_register.bombers_notebook)
    game::ui::OpenScreen(game::ui::ScreenType::Schedule);
  if (zr && start)
    game::ui::OpenScreen(game::ui::ScreenType::Quest);
  if (zr && select) {
    // Clear map screen type. (Needed because the screen could be in "soaring" mode.)
    util::Write<u8>(game::ui::GetScreen(game::ui::ScreenType::Map), 0x78E, 0);
    game::ui::OpenScreen(game::ui::ScreenType::Map);
    gctx->pad_state.input.buttons.Clear(game::pad::Button::Select);
    gctx->pad_state.input.new_buttons.Clear(game::pad::Button::Select);
  }
}

}  // namespace rnd

extern "C" {
extern char* fake_heap_start;
extern char* fake_heap_end;
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));

RST_HOOK void _start(void) {
  // Just in case something needs to be dynamically allocated...
  static char s_fake_heap[0x80000];
  fake_heap_start = &s_fake_heap[0];
  fake_heap_end = &s_fake_heap[sizeof(s_fake_heap)];

  for (size_t i = 0; i < size_t(__init_array_end - __init_array_start); i++)
    __init_array_start[i]();
}
}
