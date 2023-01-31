/**
 * @file camera.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "game/camera.h"

#include "common/advanced_context.h"
#include "common/utils.h"
#include "game/context.h"
#include "game/pad.h"

namespace game {

  u32 Camera::ChangeMode(CameraMode mode, u32 unknown) {
    return rnd::util::GetPointer<u32(Camera*, CameraMode, u32)>(0x18B31C)(this, mode, unknown);
  }

}  // namespace game
