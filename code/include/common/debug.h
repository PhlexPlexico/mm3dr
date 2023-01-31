/**
 * @file debug.h
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#ifndef _COMMON_DEBUG_H
#define _COMMON_DEBUG_H

#include "common/printf.h"

#include "z3d/z3DVec.h"

namespace rnd::util {
  /// Prints a debug message using svcOutputDebugString.
  void Print(const char* format, ...);

}  // namespace rnd::util

#endif