#include "rnd/link.h"

/**
 * @file link.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */

namespace rnd::link {

  extern "C" bool ShouldUseZoraFastSwim() {
    const auto& input = GetContext().gctx->pad_state.input;

    if (!input.buttons.IsSet(game::pad::Button::A))
      return false;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    rnd::util::Print("%s: Our current fast swim is %u and we are in fast swim.\n", __func__,
                     GetContext().use_fast_swim);
#endif
    // Toggle fast swim with D-Pad Up/Down or ZL
    if (input.new_buttons.IsOneSet(game::pad::Button::Up, game::pad::Button::Down, game::pad::Button::ZL)) {
      GetContext().use_fast_swim ^= true;
    }

    // Overrides
    if (input.buttons.IsSet(game::pad::Button::R))
      return true;
    if (input.buttons.IsSet(game::pad::Button::ZR))
      return false;

    return GetContext().use_fast_swim;
  }

  void FixSpeedIssues() {
    // This reverts some of the MM3D changes to form-specific parameters.

    // Fix Deku Link's walk acceleration value
    auto& deku_param = game::act::GetFormParam(game::act::FormParamIndex::Deku);
    deku_param.run_accel = 200;

    // Make Giant Link less painfully slow
    auto& giant_param = game::act::GetFormParam(game::act::FormParamIndex::Giant);
    giant_param.run_accel = 100;
    giant_param.walk_speed = 350;
  }

  void HandleFastOcarina(game::GlobalContext* gctx) {
  // If the Tatl prompt is visible, do not enable the ocarina D-Pad button.
  if (game::ui::GetCommonLayouts().hud->tatl_state != game::ui::TatlHudState::Hidden)
    return;

  if (!game::HasOcarina())
    return;

  if (auto* player = gctx->GetPlayerActor();
      player && gctx->hud_state.item_btn_opacity[4] == 0xFF &&
      player->controller_info.state->input.new_buttons.IsSet(game::pad::Button::Right)) {
    player->action_type = game::act::Player::ActionType::OcarinaOrTransformation;
    player->action = game::Action::Ocarina;
  }
}

}  // namespace rnd::link