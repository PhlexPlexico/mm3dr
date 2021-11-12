#include "game/actorresource.h"

namespace game::ActorResources {

  u32 find(ActorResources *resources, int object_id) {
    return rnd::util::GetPointer<u32(ActorResources *, int)>(0x1F57DC)(resources, object_id);
  }

  // Returns a value of (ObjectBankArchive->field_0 + 1 & 0xff) - 1 - It's the Actors Object ID!
  u32 loadActorResource(ObjectBankArchive *archive, u32 actor_id) {
    return rnd::util::GetPointer<u32(ObjectBankArchive *, u32)>(0x4C01CC)(archive, actor_id);
  }

}