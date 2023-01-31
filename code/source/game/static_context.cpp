/**
 * @file static_context.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "game/static_context.h"

#include "common/utils.h"

namespace game {

  StaticContext& GetStaticContext() {
    return *rnd::util::GetPointer<StaticContext>(0x7892D0);
  }

}  // namespace game
