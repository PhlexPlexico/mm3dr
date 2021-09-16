#include "game/random.h"

#include "common/utils.h"

namespace game {

u32 RandomInt() {
  return rnd::util::GetPointer<u32()>(0x14F55C)();
}

float RandomFloat() {
  return rnd::util::GetPointer<float()>(0x20A8F8)();
}

}  // namespace game
