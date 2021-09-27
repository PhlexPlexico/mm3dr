#include "rnd/item_effect.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include "z3d/z3Dvec.h"

namespace rnd {
  void ItemEffect_None(game::CommonData *comData, s16 arg1, s16 arg2) {
    return;
  }

  void ItemEffect_FullHeal(game::CommonData *comData, s16 arg1, s16 arg) {
    //With the No Health Refills option on, store-bought health upgrades do not heal the player
    if ((gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NOREFILL) && (gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NODROPREFILL)) {
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

  void ItemEffect_GiveRazorSword(game::CommonData *comData, s16 arg1, s16 arg2) {
    comData->save.player.razor_sword_hp = 100;                                // Set to 100 hits. Maybe randomize?
    comData->save.equipment.sword_shield.sword = game::SwordType::RazorSword; // Set sword to razor.
  }

  void ItemEffect_GiveGildeddSword(game::CommonData *comData, s16 arg1, s16 arg2) {
    comData->save.equipment.sword_shield.sword = game::SwordType::GildedSword; // Set sword to gilded.
  }

  void ItemEffect_GiveBottle(game::CommonData *comData, s16 bottleItemId, s16 arg2) {
    for (u32 i = 0; i <= 7; i++) {
      if (comData->save.inventory.bottles[i] == game::ItemId::None) {
        comData->save.inventory.bottles[i] = (game::ItemId)bottleItemId;
        return;
      }
    }
  }

  void ItemEffect_GiveSmallKey(game::CommonData *saveCtx, s16 dungeonId, s16 arg2) {
    s8 keys;
    switch (dungeonId) {
    case 0:
      keys = saveCtx->save.inventory.woodfall_temple_keys < 0 ? 0 : saveCtx->save.inventory.woodfall_temple_keys;
      saveCtx->save.inventory.woodfall_temple_keys = keys + 1;
      break;
    case 1:
      keys = saveCtx->save.inventory.snowhead_temple_keys < 0 ? 0 : saveCtx->save.inventory.snowhead_temple_keys;
      saveCtx->save.inventory.snowhead_temple_keys = keys + 1;
      break;
    case 2:
      keys = saveCtx->save.inventory.great_bay_temple_keys < 0 ? 0 : saveCtx->save.inventory.great_bay_temple_keys;
      saveCtx->save.inventory.great_bay_temple_keys = keys + 1;
      break;
    case 3:
      keys = saveCtx->save.inventory.stone_tower_temple_keys < 0 ? 0 : saveCtx->save.inventory.stone_tower_temple_keys;
      saveCtx->save.inventory.stone_tower_temple_keys = keys + 1;
      break;
    default:
      break;
    }
  }

  void ItemEffect_GiveDoubleMagic(game::CommonData *saveCtx, s16 arg1, s16 arg2) {
    saveCtx->save.player.magic_size_type = 2;
    saveCtx->magic_max_2 = 2;
    saveCtx->save.player.magic_num_upgrades = 1;
    saveCtx->save.player.magic_acquired = 3;
    // So you can't use the shoot button without nuts assigned to B. If they are not assigned, assign them.
    if (saveCtx->save.equipment.data[3].item_btns[0] != game::ItemId::DekuNuts)
      saveCtx->save.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    saveCtx->magic_accumulator = 0x60; // Fill meter
    return;
  }

  void ItemEffect_GiveOcarina(game::CommonData *saveCtx, s16 arg1, s16 arg2) {
    game::GiveItem(game::ItemId::Ocarina);
    return;
  }

  // TODO
  /*  void ItemEffect_IceTrap(SaveContext* saveCtx, s16 arg1, s16 arg2) {
      IceTrap_Push((u16)arg1 << 16 | (u16)arg2);
  }*/

  void ItemEffect_GiveSong(game::CommonData *saveCtx, s16 questBit, s16 arg2) {
    game::GiveItem((game::ItemId)questBit);
    //saveCtx->save.inventory.collect_register[questBit] = 1;

    // give epona for Skip Epona Race setting
    // TODO: Skip shooting test.
    /*if (questBit == 14 && gSettingsContext.skipEponaRace == SKIP) {
        saveCtx->eventChkInf[0x1] |= 0x0100;
        gSaveContext.horseData.pos.y = 0xF000; // place Epona OoB, so you can't reach her without playing the song
    }*/
  }

  void ItemEffect_GiveUpgrade(game::CommonData *saveCtx, s16 arg1, s16 arg2) {
    // This takes care of the item upgrade in inventory_count_register.
    util::GetPointer<void(u8, u8)>(0x023BF4C)(arg2, arg1);
    if (gSettingsContext.ammoDrops == (u8)AmmoDropsSetting::AMMODROPS_NONE) {
      switch (arg2) {
      // Arrows
      case 0:
        saveCtx->save.inventory.item_counts[6] += 10;
        break;
      // Bombs
      case 1:
        saveCtx->save.inventory.item_counts[11] += 10;
        break;
      // Deku Sticks
      case 6:
        saveCtx->save.inventory.items[(u32)game::ItemId::DekuStick] = game::ItemId::DekuStick;
        saveCtx->save.inventory.item_counts[13] += 10;
        break;
      // Deku Nuts
      case 7:
        saveCtx->save.inventory.items[(u32)game::ItemId::DekuNuts] = game::ItemId::DekuNuts;
        saveCtx->save.inventory.item_counts[14] += 10;
        break;
      }
    } else {
      switch (arg2) {
      case 0:
        saveCtx->save.inventory.item_counts[6] = (20 + 10 * arg1);
        break;
      case 1:
        saveCtx->save.inventory.item_counts[11] = (10 + 10 * arg1);
        break;
      case 6:
        saveCtx->save.inventory.items[(u32)game::ItemId::DekuStick] = game::ItemId::DekuStick;
        saveCtx->save.inventory.item_counts[13] = (10 * arg1);
        break;
      case 7:
        saveCtx->save.inventory.items[(u32)game::ItemId::DekuNuts] = game::ItemId::DekuNuts;
        saveCtx->save.inventory.item_counts[14] = (10 + 10 * arg1);
        break;
      }
    }
  }

  void ItemEffect_BeanPack(game::CommonData *saveCtx, s16 arg1, s16 arg2) {
    game::GiveItem(game::ItemId::MagicBean);
    saveCtx->save.inventory.item_counts[15] += 10; // 10 Magic Beans
    return;
  }

  void ItemEffect_FillWalletUpgrade(game::CommonData *saveCtx, s16 arg1, s16 arg2) {
    if (gSettingsContext.startingMaxRupees) {
        if (arg1 == 1) {
            saveCtx->save.rupee_accumulator = 200;
        } else if (arg1 == 2) {
            saveCtx->save.rupee_accumulator = 500;
        }
    }
  }

  void ItemEffect_GiveMedallion(game::CommonData *saveCtx, s16 mask, s16 arg2) {
    game::GiveItem((game::ItemId)mask);
  }

} // namespace rnd