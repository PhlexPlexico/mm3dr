#include "common/hidstate.h"

namespace rnd {
AdvanceState& GetAdvState() {
    static AdvanceState s_advstate{};
    return s_advstate;
}
}  // namespace rnd
