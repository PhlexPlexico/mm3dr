#include "game/pad.h"

#include "common/utils.h"

namespace game::pad {

ControllerMgr& GetControllerMgr() {
  return *rnd::util::GetPointer<ControllerMgr>(0x729000);
}

}  // namespace game::pad
