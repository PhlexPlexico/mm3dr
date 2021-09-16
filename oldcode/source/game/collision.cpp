#include "game/collision.h"

#include <string>

#include "common/advanced_context.h"
#include "common/debug.h"
#include "common/utils.h"

namespace game {

struct GlobalContext;

void EmitDamageEffect(const CollisionInfo& info, DamageEffect effect) {
  rnd::util::GetPointer<void(GlobalContext*, const CollisionInfo&, DamageEffect)>(0x51297C)(
      rnd::GetContext().gctx, info, effect);
}

// Similar to EmitDamageEffect, but additionally emits a graphical hit effect that looks similar
// to a light arrow hit.
void EmitDamageEffectForBossCycle(const CollisionInfo& info) {
  rnd::util::GetPointer<void(GlobalContext*, const CollisionInfo&)>(0x5149B0)(
      rnd::GetContext().gctx, info);
}

void EmitDamageFlash(const act::Actor& actor, int a, int b, int c, int d) {
  rnd::util::GetPointer<void(const act::Actor&, int, int, int, int)>(0x51E214)(actor, a, b, c, d);
}

void PrintCollision(const CollisionInfo* info, size_t count, std::string_view description) {
  std::string s{description};
  s += ' ';
  for (size_t i = 0; i < count; ++i) {
    s += rnd::util::StringFromFormat("%zu=%02x ", i, info[i].flags1.flags);
  }
  rnd::util::Print(s);
}

}  // namespace game
