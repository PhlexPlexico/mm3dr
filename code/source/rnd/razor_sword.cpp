#include "rnd/razor_sword.h"
#include "common/utils.h"
#include "rnd/settings.h"
#include "z3d/z3Dvec.h"

namespace rnd {
  u16 RS_SetDurability(void) {
    u32 randomInt = rnd::util::GetPointer<u32(void)>(0x014f55c)();
    switch ((RSDURABILITYSetting)gSettingsContext.rsDurability) {
    case RSDURABILITYSetting::RSDURABILITY_RANDOMRISK:
      return Bias(Hash(randomInt)) + 1;
    case RSDURABILITYSetting::RSDURABILITY_RANDOMSAFE:
      return 10 + (randomInt % 41);
    case RSDURABILITYSetting::RSDURABILITY_VANILLA:
      return 100;
    }
    return 100;
  }
}
