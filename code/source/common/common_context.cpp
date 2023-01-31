/**
 * @file common_context.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#include "common/advanced_context.h"

namespace rnd {

  Context& GetContext() {
    static Context s_context{};
    return s_context;
  }

}  // namespace rnd
