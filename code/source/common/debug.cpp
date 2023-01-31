/**
 * @file debug.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */

#include "common/debug.h"
#include "game/common_data.h"

extern "C" {
#include <3ds/svc.h>
}

namespace rnd::util {

  void Print(const char* format, ...) {
    char buffer[0x200];
    va_list arg;
    va_start(arg, format);
    const int written = vsnprintf_(buffer, sizeof(buffer), format, arg);
    va_end(arg);
    if (written >= 0)
      svcOutputDebugString(buffer, sizeof(buffer));
  }

}  // namespace rnd::util
