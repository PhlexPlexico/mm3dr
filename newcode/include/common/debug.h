#ifndef _COMMON_DEBUG_H
#define _COMMON_DEBUG_H

#include <array>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <string_view>

#include "z3d/z3Dvec.h"



/// Prints a debug message using svcOutputDebugString.
void Print(const char* string);
/// Prints a debug message using svcOutputDebugString.
__attribute__((format(printf, 1, 2))) void Print(const char* format, ...);

/// Only use this for debugging as this causes <string> code to be included.
__attribute__((format(printf, 1, 2))) inline std::string StringFromFormat(const char* format, ...) {
  std::string string;
  va_list arg, arg2;
  va_start(arg, format);
  va_copy(arg2, arg);
  const int size = vsnprintf(nullptr, 0, format, arg);
  if (size > 0) {
    string.resize(size);
    vsnprintf(string.data(), string.size() + 1, format, arg2);
  }
  va_end(arg);
  va_end(arg2);
  return string;
}

/// Returns the in-game time as a null-terminated HH:MM string.
std::array<char, 6> TimeToString();

#endif