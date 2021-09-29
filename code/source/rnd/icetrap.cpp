#include "rnd/icetrap.h"

namespace rnd {
  static u8 gPendingFreezes = 0;
  
  void IceTrap_Push() {
    if (gPendingFreezes < 0xFF)
      gPendingFreezes += 1;
  }

  void IceTrap_Give() {
    game::GlobalContext *gctx = GetContext().gctx;
    game::act::Player *link = gctx->GetPlayerActor();
    if(link->flags1.IsOneSet(game::act::Player::Flag1::FreezeLink, game::act::Player::Flag1::FreezeWorld)) {
      return;
    } else if (gPendingFreezes && link->timer == 0) {
      gPendingFreezes -= 1;
      rnd::util::GetPointer<void(game::GlobalContext*, game::act::Player*, int, int16_t, char, int)>(0x239794)(gctx, link, 3, 1, 0, 1);
    }
    return;
  }
  bool IceTrap_IsPending() {
    return gPendingFreezes > 0;
  }
} // namespace rnd