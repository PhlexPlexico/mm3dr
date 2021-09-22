#include "common/debug.h"

#include "game/common_data.h"

namespace rst::util {

extern "C" {
int svcOutputDebugString(const char* string, int length);
}

void Print(std::string_view string) {
  svcOutputDebugString(string.data(), string.size());
}

}
