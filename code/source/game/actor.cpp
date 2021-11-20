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
