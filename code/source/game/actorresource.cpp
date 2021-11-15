#include "game/actorresource.h"

namespace game::ActorResource {

  u32 find(ActorResources *resources, int object_id) {
    return rnd::util::GetPointer<u32(ActorResources *, int)>(0x1F57DC)(resources, object_id);
  }

  // Returns a value of (ObjectBankArchive->field_0 + 1 & 0xff) - 1 - It's the Actors Object ID!
  u32 loadActorResource(ActorResources *archive, u32 actor_id) {
    return rnd::util::GetPointer<u32(ActorResources *, u32)>(0x4C01CC)(archive, actor_id);
  }

  void freeActorResource(ActorResource *resource) {
    return rnd::util::GetPointer<void(ActorResource *)>(0x14E8F4)(resource);
  }

}

//0x804af5c
//0x804af5c Object Context - Watch point this
// 804af58
// 8041b20 Fairly static global context.