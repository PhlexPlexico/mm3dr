#include "common/advanced_context.h"

namespace rnd {

Context& GetContext() {
  static Context s_context{};
  return s_context;
}

}  // namespace rnd
