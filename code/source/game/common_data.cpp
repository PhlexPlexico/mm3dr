/**
 * @file common_data.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "game/common_data.h"

#include "common/utils.h"

namespace game {

  CommonData& GetCommonData() {
    // Right before the static context in .bss.
    return *rnd::util::GetPointer<CommonData>(0x7751D8);
  }

}  // namespace game
