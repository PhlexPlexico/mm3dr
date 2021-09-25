#include "rnd/item_effect.h"
#include "rnd/settings.h"
#include "rnd/savefile.h"
#include "z3d/z3Dvec.h"

namespace rnd {
  void ItemEffect_None(game::CommonData *comData, s16 arg1, s16 arg2) {
    return;
  }
  
  void ItemEffect_FullHeal(game::CommonData *comData, s16 arg1, s16 arg) {
    //With the No Health Refills option on, store-bought health upgrades do not heal the player
    if((gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NOREFILL)\
    && (gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NODROPREFILL)){
        comData->health_accumulator = 20 * 0x10;
    }
    return;
  }

  void ItemEffect_GiveGiantsWallet(game::CommonData *comData, s16 arg1, s16 arg) {
    comData->save.inventory.inventory_count_register.wallet_upgrade = 2;
    if (gSettingsContext.startingMaxRupees)
        comData->save.player.rupee_count = 999;
    return;
  }

  void ItemEffect_GiveRazorSword(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.player.razor_sword_hp = 100; // Set to 100 hits.
    comData->save.equipment.sword_shield.sword = game::SwordType::RazorSword; // Set sword to razor.
  }

  void ItemEffect_GiveGildeddSword(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.equipment.sword_shield.sword = game::SwordType::GildedSword; // Set sword to razor.
  }

  
  void ItemEffect_GiveBottle(game::CommonData* comData, s16 bottleItemId, s16 arg2) {
      for (u32 i = 0; i <= 7; i++) {
          if (comData->save.inventory.bottles[i] == game::ItemId::None) {
              comData->save.inventory.bottles[i] = (game::ItemId)bottleItemId;
              return;
          }
      }
  }
} // namespace rnd