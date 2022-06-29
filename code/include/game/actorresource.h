#ifndef _GAME_ACTOR_RESOURCE_H
#define _GAME_ACTOR_RESOURCE_H
#define OBJECT_EXCHANGE_BANK_MAX 36

#include "common/types.h"
#include "common/utils.h"
#include "game/objectbankarchive.h"

namespace game::ActorResource {
  // Same as ObjectStatus in OoT3DR
  struct ActorResource {
    u16 object_id;
    u16 field_2;
    ResArchiveHeader* file_data;
    u32 file_size;
    u32 file;
    game::ObjectBank::ObjectBankArchive archive;
  };
  static_assert(sizeof(ActorResource) == 0xAC);

  struct ActorResources {
    u8 flags;
    u8 field_1;
    u8 field_2;
    u8 field_3;
    ActorResource resources[387];
  };
  static_assert(sizeof(ActorResources) == 0x10408);

  struct ObjectContext {
    u8 num;
    char gap_01[7];
    ActorResource status[OBJECT_EXCHANGE_BANK_MAX];
  };
  static_assert(sizeof(ObjectContext) == 0x1838);

  u32 find(ActorResources*, int);
  u32 loadActorResource(ActorResources*, u32);
  void freeActorResource(ActorResource*);

}  // namespace game::ActorResource

#endif