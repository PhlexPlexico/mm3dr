#include "game/ui/screens/gearscreen.h"

namespace game::ui::screens {
  GearScreen* GetGearScreen() {
    return rnd::util::GetPointer<GearScreen>(0x6F4130);
  }

}  // namespace game::ui::screens