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
    if (gSettingsContext.enableFastOcarina == 0) {
      return;
    }
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

  struct FastArrowState {
    std::optional<game::Action> override_action;
    /// The item button slot that was used with the override_action.
    std::optional<u8> item_btn_slot;
    int magic_cost_update_timer = -1;
  };

  static FastArrowState s_fast_arrow_state{};

  struct ArrowTypeInfo {
    const char* name;
    int magic_cost;
    game::ItemId required_item;
  };

  static constexpr ArrowTypeInfo s_arrow_types[] = {
      {"Arrow", 0, game::ItemId::Arrow},
      {"Fire Arrow", 4, game::ItemId::FireArrow},
      {"Ice Arrow", 4, game::ItemId::IceArrow},
      {"Light Arrow", 8, game::ItemId::LightArrow},
  };

  static void SpawnArrowActor(game::GlobalContext* gctx, game::act::Player* player) {
    game::CommonData& cdata = game::GetCommonData();

    const auto info = player->GetArrowInfo(gctx);
    if (!info.can_use) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: cannot use arrow\n", __func__);
#endif
      return;
    }

    u16 param = info.actor_param;
    int type = int(param) - 2;
    if (type < 0 || size_t(type) > std::size(s_arrow_types))
      return;

    if (cdata.save.player.magic < s_arrow_types[type].magic_cost) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: not enough magic for %s (%d < %d) -- falling back to normal arrow\n", __func__,
                  s_arrow_types[type].name, cdata.save.player.magic, s_arrow_types[type].magic_cost);
#endif
      type = 0;
      param = 2;
    }

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    util::Print("%s: spawning %s (param=%u)\n", __func__, s_arrow_types[type].name, param);
#endif

    auto* arrow = gctx->SpawnActor(player, game::act::Id::Arrow, 0, player->angle.y, 0, param, player->pos.pos);
    player->projectile_actor = arrow;
    cdata.magic_cost = 0;
    // For some reason, updating the magic cost immediately doesn't work,
    // so delay the update by 2 frames.
    if (type != 0)
      s_fast_arrow_state.magic_cost_update_timer = 2;
  }

  void HandleFastArrowSwitch(game::act::Player* player) {
    if (gSettingsContext.enableFastArrowSwap == 0) {
      return;
    }
    game::CommonData& cdata = game::GetCommonData();
    game::GlobalContext* gctx = GetContext().gctx;

    // Reset the override action if the player is not using a bow.
    constexpr u8 first = u8(game::Action::Arrow);
    constexpr u8 last = u8(game::Action::LightArrow);
    const bool is_using = player->action_type == game::act::Player::ActionType::Type3 || player->projectile_actor;
    if (first > u8(player->current_action) || u8(player->current_action) > last || !is_using) {
      s_fast_arrow_state = {};
      return;
    }

    if (s_fast_arrow_state.item_btn_slot != player->item_btn_slot) {
      // The player switched to a different item button slot.
      // Reset the action override and any other internal state.
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: detected item button slot change, resetting.\n", __func__);
#endif
      s_fast_arrow_state = {};
    }

    s_fast_arrow_state.item_btn_slot = player->item_btn_slot;

    if (s_fast_arrow_state.magic_cost_update_timer > 0)
      --s_fast_arrow_state.magic_cost_update_timer;

    if (s_fast_arrow_state.override_action && s_fast_arrow_state.magic_cost_update_timer == 0) {
      const u8 type = u8(*s_fast_arrow_state.override_action) - first;
      game::act::PlayerUpdateMagicCost(gctx, s_arrow_types[type].magic_cost, 0,
                                       game::act::AllowExistingMagicUsage::Yes);
      s_fast_arrow_state.magic_cost_update_timer = -1;
    }

    if (!s_fast_arrow_state.override_action) {
      s_fast_arrow_state.override_action = player->current_action;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: override_action is now %u\n", __func__, u8(*s_fast_arrow_state.override_action));
#endif
    }

    if (gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Up)) {
      int idx = u8(*s_fast_arrow_state.override_action) - first;

      auto can_use_arrow = [&cdata](int idx) {
        return game::HasItem(s_arrow_types[idx].required_item) &&
               cdata.save.player.magic >= s_arrow_types[idx].magic_cost &&
               game::CanUseItem(s_arrow_types[idx].required_item);
      };

      // Ensure we don't enter an infinite loop if no other arrow type can be used.
      if (!can_use_arrow(idx))
        return;

      do {
        idx = (idx + 1) % std::size(s_arrow_types);
      } while (!can_use_arrow(idx));

      s_fast_arrow_state.override_action = static_cast<game::Action>(idx + first);
      player->current_action = player->action = *s_fast_arrow_state.override_action;
      cdata.save.equipment.data[0].item_btns[player->item_btn_slot] = s_arrow_types[idx].required_item;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      util::Print("%s: override_action is now %u (%s)\n", __func__, u8(*s_fast_arrow_state.override_action),
                  s_arrow_types[idx].name);
#endif

      if (player->projectile_actor) {
        player->projectile_actor->Free();
        player->projectile_actor = nullptr;
        SpawnArrowActor(gctx, player);
      }
    }
  }

  void FixFreeCameraReset() {
    using namespace game;
    auto* gctx = GetContext().gctx;
    auto* player = gctx->GetPlayerActor();

    // Only reset free camera when Z-targeting and when free camera is active
    if (!player)
      return;
    if (gctx->main_camera.mode != CameraMode::FREECAMERA)
      return;
    if (!gctx->pad_state.input.buttons.IsSet(pad::Button::L))
      return;

    if (player->flags3.IsSet(act::Player::Flag3::ZoraFastSwimming)) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      rnd::util::Print("%s: resetting camera mode (Zora swimming)\n", __func__);
#endif
      const bool in_water = player->flags1.IsSet(act::Player::Flag1::InWater);
      gctx->main_camera.ChangeMode(in_water ? CameraMode::GORONDASH : CameraMode::FREEFALL);
    } else if (player->flags3.IsSet(act::Player::Flag3::GoronRolling)) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      rnd::util::Print("%s: resetting camera mode (Goron rolling)\n", __func__);
#endif
      const bool on_ground = player->flags_94.IsSet(act::Actor::Flag94::Grounded);
      gctx->main_camera.ChangeMode(on_ground ? CameraMode::GORONDASH : CameraMode::GORONJUMP);
    }
  }

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

  bool CheckIfMagicAcquired() {
    const game::CommonData& cdata = game::GetCommonData();
    if (cdata.save.player.magic_acquired == 0)
      return 0;
    else
      return 1;
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

  void SongOfTimeSwordPlacement() {
    game::SaveData& saveData = game::GetCommonData().save;
    // Check to see if we received any sword upgrades.
    if (gExtSaveData.givenItemChecks.progressiveSwordUpgrade == 1) {
      saveData.equipment.data[0].item_btn_b = game::ItemId::RazorSword;
      saveData.equipment.sword_shield.sword = game::SwordType::RazorSword;
      return;
    } else if (gExtSaveData.givenItemChecks.progressiveSwordUpgrade == 2) {
      saveData.equipment.data[0].item_btn_b = game::ItemId::GildedSword;
      saveData.equipment.sword_shield.sword = game::SwordType::GildedSword;
      return;
    }
    if (gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_NONE &&
        saveData.equipment.sword_shield.sword == game::SwordType::NoSword) {
      return;
    }

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    rnd::util::Print("%s: Sword is %u and starting sword is %u\n", __func__, saveData.equipment.sword_shield.sword,
                     gSettingsContext.startingKokiriSword);
#endif
    // Check sword/shield flag to see what sword to give back. Once we do that, set the form[0] of player
    // equipment to that sword and return.
    if (saveData.equipment.sword_shield.sword == game::SwordType::NoSword &&
        gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_KOKIRI) {
      saveData.equipment.data[0].item_btn_b = game::ItemId::KokiriSword;
      saveData.equipment.sword_shield.sword = game::SwordType::KokiriSword;
    } else if (saveData.equipment.sword_shield.sword == game::SwordType::NoSword &&
               gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_RAZOR) {
      saveData.equipment.data[0].item_btn_b = game::ItemId::RazorSword;
      saveData.equipment.sword_shield.sword = game::SwordType::RazorSword;
    }
    return;
  }
  }

}  // namespace rnd::link