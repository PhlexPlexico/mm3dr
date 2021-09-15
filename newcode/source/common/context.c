#include "common/context.h"


Context& GetContext() {
  static Context s_context{};
  return s_context;
}