#include "common/debug.h"
#include "game/common_data.h"

extern "C" {
#include <3ds/svc.h>
}

namespace rnd::util {

  void Print(const char *format, ...) {
    char buffer[0x200];
    va_list arg;
    va_start(arg, format);
    const int written = vsnprintf_(buffer, sizeof(buffer), format, arg);
    va_end(arg);
    if (written >= 0)
      svcOutputDebugString(buffer, sizeof(buffer));
  }

}
