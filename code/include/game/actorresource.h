#ifndef _GAME_ACTOR_RESOURCE_H
#define _GAME_ACTOR_RESOURCE_H

#include "common/types.h"
#include "common/utils.h"
#include "game/objectbankarchive.h"

namespace game::ActorResource {
  // Same as ObjectStatus in OoT3DR
  struct ActorResource {
    u16 object_id;
    u16 field_2;
    u32 file_data;
    u32 file_size;
    u32 file;
    game::ObjectBank::ObjectBankArchive archive;
    
  };
  static_assert(sizeof(ActorResource) == 0xAC);

  // Same as ObjectContext in OoT3DR
  struct ActorResources {
    u8 flags;
    u8 field_1;
    u8 field_2;
    u8 field_3;
    ActorResource resources[387];
    u32 find(ActorResources*, int);
    
  };
  static_assert(sizeof(ActorResources) == 0x10408);

  u32 loadActorResource(game::ObjectBank::ObjectBankArchive*, u32);
  void freeActorResource(ActorResource*);

} // namespace game

#endif