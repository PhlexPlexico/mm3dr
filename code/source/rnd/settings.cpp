#include "rnd/settings.h"

namespace rnd {
  SettingsContext gSettingsContext = {0};
  u8 Damage32 = 0;

  s32 Settings_ApplyDamageMultiplier(game::GlobalContext *globalCtx, s32 changeHealth) {
    game::SaveData& saveData = game::GetCommonData().save;
    // Fairy healing also gets sent to this function and should be ignored
    if (changeHealth >= 0) {
      return changeHealth;
    }
    // If supposed to take damage on OHKO ignore everything else
    if (gSettingsContext.damageMultiplier == (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_OHKO) {
      return -1000;
    }

    s32 modifiedChangeHealth = changeHealth;

    if (modifiedChangeHealth < 0) {
      switch (gSettingsContext.damageMultiplier) {
      case (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_HALF:
        modifiedChangeHealth /= 2;
        break;
      case (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_DEFAULT:
        break;
      case (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_DOUBLE:
        modifiedChangeHealth *= 2;
        break;
      case (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_QUADRUPLE:
        modifiedChangeHealth *= 4;
        break;
      case (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_OCTUPLE:
        modifiedChangeHealth *= 8;
        break;
      case (u8)DamageMultiplierSetting::DAMAGEMULTIPLIER_SEXDECUPLE:
        modifiedChangeHealth *= 16;
        break;
      }

      // Can only be 0 if supposed to be -0.5: alternate -1 and 0
      if (modifiedChangeHealth == 0) {
        modifiedChangeHealth = -(Damage32 & 1);
        Damage32 ^= 1;
      }
    }

    // Double defense seems to round up after halving so values of -1 should instead alternate between -2 and 0 (-1 would also work, but -2 was easier)
    if (saveData.player.double_defense == 1 && modifiedChangeHealth == -1) {
      modifiedChangeHealth = -(Damage32 & 2);
      Damage32 ^= 2;
    }

    return modifiedChangeHealth;
  }
  //With the No Health Refill option on, full health refills from health upgrades and Bombchu Bowling are turned off, and fairies restore 3 hearts
  //Otherwise, they grant a full heal, and the default effect applies (full heal from bottle, 8 hearts on contact)
  u32 Settings_SetFullHealthRestore(u8 setAmount) {
    if ((gSettingsContext.heartDropRefill == (u8)HeartDropRefillSetting::HEARTDROPREFILL_NOREFILL) \
    || (gSettingsContext.heartDropRefill == (u8)HeartDropRefillSetting::HEARTDROPREFILL_NODROPREFILL)) {
      return setAmount;
    } else {
      return 0x140;
    }
  }
  u32 NoHealFromHealthUpgrades(void) {
    return Settings_SetFullHealthRestore(0);
  }
  u32 NoHealFromBombchuBowlingPrize(void) {
    return Settings_SetFullHealthRestore(0);
  }
  u32 FairyReviveHealAmount(void) {
    return Settings_SetFullHealthRestore(0x30);
  }
  u32 FairyUseHealAmount(void) {
    return Settings_SetFullHealthRestore(0x30);
  }
  // TODO: Change the addr 
 /* typedef void (*Health_ChangeBy_proc)(GlobalContext *arg1, u32 arg2);
#define Health_ChangeBy_addr 0x352dbc
#define Health_ChangeBy ((Health_ChangeBy_proc)Health_ChangeBy_addr)
  void FairyPickupHealAmount(void) {
    if (gSettingsContext.heartDropRefill == HeartDropRefillSetting::HEARTDROPREFILL_NOREFILL \
    || gSettingsContext.heartDropRefill == HeartDropRefillSetting::HEARTDROPREFILL_NODROPREFILL) {
      Health_ChangeBy(gGlobalContext, 0x30);
    } else {
      Health_ChangeBy(gGlobalContext, 0x80);
    }
  }*/

  // From section 5 of https://www.cs.ubc.ca/~rbridson/docs/schechter-sca08-turbulence.pdf
  u32 Hash(u32 state) {
    // Added salt based on the seed hash so traps in the same location in different seeds can have different effects
    u32 salt = 0;
    for (int i = 0; i < 5; i++) {
      salt |= gSettingsContext.hashIndexes[i] << (i * 6);
    }
    state ^= salt;

    state ^= 0xDC3A653D;
    state *= 0xE1C88647;
    state ^= state >> 16;
    state *= 0xE1C88647;
    state ^= state >> 16;
    state *= 0xE1C88647;

    return state;
  }

  u8 And(u32 seed, u8 start, u8 end) {
    u8 value = 1;

    for (u8 i = start; i < end && value; i++) {
      value &= seed >> i;
    }

    return value;
  }

  u8 Bias(u32 seed) {
    u8 value = (seed & 0x00000007);
    value |= And(seed, 3, 5) << 3;
    value |= And(seed, 5, 7) << 4;
    value |= And(seed, 7, 11) << 5;
    value |= And(seed, 11, 16) << 6;
    return value;
  }

  //TODO: Change hash icon names
  const char hashIconNames[32][25] = {
      "Deku Stick",
      "Deku Nut",
      "Bow",
      "Slingshot",
      "Ocarina",
      "Bombchu",
      "Longshot",
      "Boomerang",
      "Lens of Truth",
      "Beans",
      "Megaton Hammer",
      "Bottled Fish",
      "Bottled Milk",
      "Mask of Truth",
      "SOLD OUT",
      "Cucco",
      "Mushroom",
      "Saw",
      "Frog",
      "Master Sword",
      "Mirror Shield",
      "Kokiri Tunic",
      "Hover Boots",
      "Silver Gauntlets",
      "Gold Scale",
      "Shard of Agony",
      "Skull Token",
      "Heart Container",
      "Boss Key",
      "Compass",
      "Map",
      "Big Magic",
  };
}
