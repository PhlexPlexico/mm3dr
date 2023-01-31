/**
 * @file actor.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */

#include "game/actor.h"

#include "common/utils.h"

namespace game::act {

  void Actor::Free() {
    draw_fn = nullptr;
    flags.Clear(Flag::Targetable);
    calc_fn = nullptr;
  }

  // Returns a pointer to the array of the Overlay Table.
  // This is known as gActorOverlay in OoT3DR.
  ActorOverlayInfo* GetActorOverlayInfoTable() {
    return rnd::util::GetPointer<ActorOverlayInfo*()>(0x657768)();
  }

}  // namespace game::act
