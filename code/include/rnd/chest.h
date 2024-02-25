#ifndef _RND_CHEST_H_
#define _RND_CHEST_H_

#include "common/advanced_context.h"
#include "game/actors/chest.h"
#include "game/context.h"
#include "rnd/item_override.h"
#include "rnd/settings.h"
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif
namespace rnd {
  enum class ChestSize : u8 {
    VANILLA_SIZE,
    SIZE_MATCHES_CONTENT,
  };

  enum class ChestAnim : u8 {
    ALWAYS_FAST,
    ANIMATION_MATCHES_CONTENT,
  };

  enum class ChestType : u8 {
    WOODEN_BIG,
    WOODEN_SMALL,
    DECORATED_BIG,
    DECORATED_SMALL,
  };

  extern "C" {
  game::actors::EnBoxType Chest_OverrideSize(game::actors::En_Box*, game::GlobalContext*);
  u8 Chest_IsOverrideEnabled(game::actors::En_Box*, u16);
  }
  // void EnBox_rInit(game::act::Actor* thisx, game::GlobalContext* globalCtx);
  // void EnBox_rUpdate(game::act::Actor* thisx, game::GlobalContext* globalCtx);
  // u8 Chest_OverrideAnimation();
  // u8 Chest_OverrideDecoration();
  // u8 Chest_OverrideIceSmoke(game::act::Actor* thisx);
}  // namespace rnd
#endif  //_CHEST_H_