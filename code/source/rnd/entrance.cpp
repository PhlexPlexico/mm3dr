#include "rnd/entrance.h"

namespace rnd {
  extern "C" {
    void Entrance_EnteredLocation(u16 sceneNum) {
    auto* gctx = rnd::GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return;
    
    
    SaveFile_SetSceneDiscovered(sceneNum);
}
  }
} // namespace rnd