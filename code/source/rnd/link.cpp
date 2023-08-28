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

  namespace {
    struct TransformAction {
      game::pad::Button trigger_btn;
      game::ItemId required_mask;
      game::Action action;
      bool usable_in_water;
      const char* name;
      bool require_zr = false;
    };
    static constexpr TransformAction s_actions[] = {
        {game::pad::Button::Left, game::ItemId::ZoraMask, game::Action::ZoraMask, true, "Zora"},
        {game::pad::Button::Up, game::ItemId::GoronMask, game::Action::GoronMask, false, "Goron"},
        {game::pad::Button::Down, game::ItemId::DekuMask, game::Action::DekuMask, false, "Deku"},
        // Second-level mappings (make sure require_zr=true!)
        {game::pad::Button::Up, game::ItemId::FierceDeityMask, game::Action::FierceDeityMask, false, "Fierce Deity",
         true},
    };
  }  // namespace

  extern "C" {
  bool ShouldUseZoraFastSwim() {
    const auto& input = GetContext().gctx->pad_state.input;

    if (!input.buttons.IsSet(game::pad::Button::A))
      return false;
    // Toggle fast swim with D-Pad Up, Down or ZL
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

  bool SwitchToZoraFastSwim(game::GlobalContext* gctx, game::act::Player* player, bool check_magic) {
    const auto do_switch = util::GetPointer<decltype(SwitchToZoraFastSwim)>(0x220EA0);
    return (player->zora_swim_a_press_duration >= 7 ||
            player->flags1.IsSet(game::act::Player::Flag1::IsUsingZoraBarrier)) &&
           do_switch(gctx, player, check_magic);
  }

  // This patch is all taken care of in ASM now. No need to loop into the main Calc function.
  void HandleFastTransform() {
    const game::GlobalContext* gctx = GetContext().gctx;

    game::act::Player* player = gctx->GetPlayerActor();
    if (!player)
      return;

    const bool in_water = player->flags1.IsSet(game::act::Player::Flag1::InWater);
    const auto it = std::find_if(std::begin(s_actions), std::end(s_actions), [&](const TransformAction& action) {
      return player->controller_info.state->input.buttons.IsSet(game::pad::Button::ZR) == action.require_zr &&
             player->controller_info.state->input.new_buttons.IsSet(action.trigger_btn) &&
             (!in_water || action.usable_in_water);
    });
    if (it == std::end(s_actions))
      return;

    if (player->active_mask_id == game::MaskId::GiantMask) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: wearing Giant's Mask, skipping\n", __func__);
#endif
      return;
    }

    if (!game::HasMask(it->required_mask)) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: player does not have the %s Mask, skipping\n", __func__, it->name);
#endif

      return;
    }

    if (!game::CanUseItem(it->required_mask)) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: CanUseItem returned false, skipping\n", __func__);
#endif
      return;
    }

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    util::Print("%s: transforming (%s)\n", __func__, it->name);
#endif

    player->action = it->action;
    player->action_type = game::act::Player::ActionType::OcarinaOrTransformation;
    // Store the transform action in case the transformation cannot be done immediately.
    // This allows the Mask Storage technique to work with the fast transform shortcuts as well.
    player->transform_mask_action = it->action;

    return;
  }

  // Weird bug fix for checking if we have the zora mask, but not have completed the extDataCheck
  // for fast mask changes and ensuring that default behaviour works as intended.
  u8 ZoraMaskCheck() {
    // This should be safe? Shouldn't hopefully cause crashes... If not please look here first!
    game::SaveData& saveData = game::GetCommonData().save;
    return static_cast<u8>(saveData.inventory.masks[17]);
  }
  }

}  // namespace rnd::link