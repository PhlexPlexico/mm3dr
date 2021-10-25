#ifndef _COMMON_DEBUG_H
#define _COMMON_DEBUG_H

#include "common/printf.h"

#include "z3d/z3Dvec.h"

namespace rnd::util {
  /// Prints a debug message using svcOutputDebugString.
  void Print(const char *format, ...);

} // namespace rnd::util

#endif