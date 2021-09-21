#include "game/sound.h"

#include <tuple>

#include "common/utils.h"
#include "game/actor.h"

namespace game::sound {

class StreamMgr;

static StreamMgr& GetStreamMgr() {
  return rnd::util::GetInstance<StreamMgr>(0x7CB49C, 0x6B0A3C, 0x1E11F8);
}

bool PlayEffect(EffectId id) {
  return rnd::util::GetPointer<bool(EffectId)>(0x2006E4)(id);
}

bool PlayEffect(const z3dVec3f& position, EffectId id) {
  return rnd::util::GetPointer<bool(const z3dVec3f&, EffectId)>(0x226218)(position, id);
}

bool PlayEffect(const act::Actor& actor, EffectId id) {
  return PlayEffect(actor.pos.pos, id);
}

StreamId GetCurrentStreamId(StreamPlayer player) {
  return rnd::util::GetPointer<StreamId(StreamMgr&, StreamPlayer)>(0x1E1194)(GetStreamMgr(),
                                                                             player);
}

bool PlayStream(StreamId id, StreamPlayer player) {
  return rnd::util::GetPointer<bool(StreamMgr&, StreamId, StreamPlayer, u32)>(0x239228)(
      GetStreamMgr(), id, player, 0xffffffff);
}

void ControlStream(StreamPlayer player, int a, int b) {
  rnd::util::GetPointer<void(StreamMgr&, StreamPlayer, int, int)>(0x1DC2F0)(GetStreamMgr(), player,
                                                                            a, b);
}

void ControlEnv(int index) {
  rnd::util::GetPointer<void(int)>(0x1883F0)(index);
}

}  // namespace game::sound
