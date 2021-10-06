#include "game/player.h"

#include "common/utils.h"
#include "game/common_data.h"
// #include "rnd/link.h"

namespace game::act {


FormParam& GetFormParam(FormParamIndex idx) {
  return rnd::util::GetPointer<FormParam>(0x7AE9E8)[u8(idx) % 8];
}

void FixSpeedIssues() {
  // This reverts some of the MM3D changes to form-specific parameters.

  // Fix Deku Link's walk acceleration value
  auto& deku_param = GetFormParam(FormParamIndex::Deku);
  deku_param.run_accel = 200;

  // Make Giant Link less painfully slow
  auto& giant_param = GetFormParam(FormParamIndex::Giant);
  giant_param.run_accel = 100;
  giant_param.walk_speed = 350;
}

Player::ArrowInfo Player::GetArrowInfo(GlobalContext* gctx) const {
  ArrowInfo info;

  if (current_action == Action::DekuBubble) {
    info.item_id = ItemId::DekuNuts;
    info.actor_param = active_form == Player::Form::Deku ? 7 : 6;
  } else {
    info.item_id = ItemId::Arrow;
    // Extension: Nintendo directly uses current_action here.
    //info.actor_param = u8(rnd::link::GetFastArrowAction().value_or(current_action)) - 7;
    info.actor_param = u8(current_action) - 7;
    if (flags1.IsSet(Player::Flag1::Riding))
      info.actor_param = 1;
  }

  const CommonData& cdata = GetCommonData();

  if (active_form == Player::Form::Deku) {
    // Playing the Honey and Darling shooting minigame as Deku Link.
    info.can_use = cdata.save.player.magic >= 2 ||
                   ((cdata.save.anonymous_72 & 1) && gctx->scene == SceneId::HoneyAndDarling);
  } else {
    info.can_use = flags3.IsSet(Flag3::DekuStuffMaybe) ||
                   (cdata.field_3696 == 1 && gctx->hud_state.field_244) || gctx->field_C531 ||
                   rnd::util::GetPointer<bool(ItemId)>(0x224EF8)(info.item_id);
  }

  return info;
}

bool Player::SetTalkActor(u8 new_fn1_idx, Actor* actor) {
  if (fn1_idx == 5)
    return false;
  if (new_fn1_idx == 6 && fn1_idx == 0)
    return false;
  fn1_idx = new_fn1_idx;
  talk_actor = actor;
  talking = 1;
  return true;
}

bool PlayerUpdateMagicCost(game::GlobalContext* gctx, int cost, int mode,
                           AllowExistingMagicUsage allow_existing_usage) {
  return rnd::util::GetPointer<bool(game::GlobalContext*, int, int, bool)>(0x2264CC)(
      gctx, cost, mode, allow_existing_usage == AllowExistingMagicUsage::Yes);
}


}  // namespace game::act
