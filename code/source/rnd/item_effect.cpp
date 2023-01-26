#include "rnd/item_effect.h"
#include "rnd/icetrap.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include "z3d/z3DVec.h"

namespace rnd {
  void ItemEffect_None(game::CommonData* comData, s16 arg1, s16 arg2) {
    return;
  }

  void ItemEffect_FullHeal(game::CommonData* comData, s16 arg1, s16 arg) {
    // With the No Health Refills option on, store-bought health upgrades do not heal the player
    if ((gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NOREFILL) &&
        (gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NODROPREFILL)) {
      comData->health_accumulator = 20 * 0x10;
    }
    return;
  }

  void ItemEffect_GiveGiantsWallet(game::CommonData* comData, s16 arg1, s16 arg) {
    comData->save.inventory.inventory_count_register.wallet_upgrade = 2;
    if (gSettingsContext.startingMaxRupees)
      comData->save.player.rupee_count = 999;
    return;
  }

  void ItemEffect_GiveKokiriSword(game::CommonData* comData, s16 arg1, s16 arg2) {
    // If we have a better sword don't give anything.
    if (comData->save.equipment.sword_shield.sword > game::SwordType::KokiriSword) {
      return;
    }
    comData->save.equipment.sword_shield.sword = game::SwordType::KokiriSword;  // Set sword to kokiri.
  }

  void ItemEffect_GiveRazorSword(game::CommonData* comData, s16 arg1, s16 arg2) {
    // If we have a better sword don't give anything.
    if (comData->save.equipment.sword_shield.sword > game::SwordType::RazorSword) {
      return;
    }
    comData->save.player.razor_sword_hp = 100;                                 // Set to 100 hits. Maybe randomize?
    comData->save.equipment.sword_shield.sword = game::SwordType::RazorSword;  // Set sword to razor.
  }

  void ItemEffect_GiveGildedSword(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.equipment.sword_shield.sword = game::SwordType::GildedSword;  // Set sword to gilded.
  }

  void ItemEffect_GiveBottle(game::CommonData* comData, s16 bottleItemId, s16 arg2) {
    for (u32 i = 0; i <= 7; i++) {
      if (comData->save.inventory.bottles[i] == game::ItemId::None) {
        comData->save.inventory.bottles[i] = (game::ItemId)bottleItemId;
        return;
      }
    }
  }

  void ItemEffect_GiveDefense(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.player.double_defense = 1;
  }

  void ItemEffect_GiveSmallKey(game::CommonData* comData, s16 dungeonId, s16 arg2) {
    s8 keys;
    switch (dungeonId) {
    case 0:
      keys = comData->save.inventory.woodfall_temple_keys < 0 ? 0 : comData->save.inventory.woodfall_temple_keys;
      comData->save.inventory.woodfall_temple_keys = keys + 1;
      break;
    case 1:
      keys = comData->save.inventory.snowhead_temple_keys < 0 ? 0 : comData->save.inventory.snowhead_temple_keys;
      comData->save.inventory.snowhead_temple_keys = keys + 1;
      break;
    case 2:
      keys = comData->save.inventory.great_bay_temple_keys < 0 ? 0 : comData->save.inventory.great_bay_temple_keys;
      comData->save.inventory.great_bay_temple_keys = keys + 1;
      break;
    case 3:
      keys = comData->save.inventory.stone_tower_temple_keys < 0 ? 0 : comData->save.inventory.stone_tower_temple_keys;
      comData->save.inventory.stone_tower_temple_keys = keys + 1;
      break;
    default:
      break;
    }
  }

  void ItemEffect_GiveGreatSpin(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.has_great_spin_0x02 = 2;
  }

  void ItemEffect_GiveDoubleMagic(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.player.magic_size_type = 0;
    comData->magic_max_2 = 1;
    comData->save.player.magic_num_upgrades = 1;
    comData->save.player.magic_acquired = 1;
    // So you can't use the shoot button without nuts assigned to B. If they are not assigned,
    // assign them.
    if (comData->save.equipment.data[3].item_btns[0] != game::ItemId::DekuNuts)
      comData->save.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    comData->save.player.magic = 0x60;  // Fill meter
  }

  void ItemEffect_GiveMagic(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.player.magic_acquired = 1;
    comData->save.player.magic_size_type = 0;
    comData->save.player.magic = 0x30;
    if (comData->save.equipment.data[3].item_btns[0] != game::ItemId::DekuNuts)
      comData->save.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    comData->save.player.magic_num_upgrades = 0;  // Single Magic
  }

  void ItemEffect_GiveProgressiveMagic(game::CommonData* comData, s16 arg1, s16 arg2) {
    if (comData->save.player.magic_acquired != 0) {
      ItemEffect_GiveDoubleMagic(comData, arg1, arg2);
    } else {
      ItemEffect_GiveMagic(comData, arg1, arg2);
    }
  }

  void ItemEffect_GiveOcarina(game::CommonData* comData, s16 arg1, s16 arg2) {
    game::GiveItem(game::ItemId::Ocarina);
    return;
  }

  void ItemEffect_GiveDoubleDefense(game::CommonData* comData, s16 arg1, s16 arg2) {
    comData->save.player.double_defense = 1;
    if ((gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NOREFILL) &&
        (gSettingsContext.heartDropRefill != (u8)HeartDropRefillSetting::HEARTDROPREFILL_NODROPREFILL)) {
      comData->health_accumulator = 20 * 0x10;
    }
  }

  void ItemEffect_IceTrap(game::CommonData* comData, s16 arg1, s16 arg2) {
    IceTrap_Push();
  }

  void ItemEffect_GiveSong(game::CommonData* comData, s16 questBit, s16 arg2) {
    switch (questBit) {
    case 1:
      comData->save.inventory.collect_register.sonata_of_awakening = 1;
      break;
    case 2:
      comData->save.inventory.collect_register.lullaby_intro = 1;
      comData->save.inventory.collect_register.goron_lullaby = 1;
      break;
    case 3:
      comData->save.inventory.collect_register.new_wave_bossa_nova = 1;
      break;
    case 4:
      comData->save.inventory.collect_register.elegy_of_emptiness = 1;
      break;
    case 5:
      comData->save.inventory.collect_register.oath_to_order = 1;
      break;
    case 6:
      comData->save.inventory.collect_register.song_of_time = 1;
      break;
    case 7:
      comData->save.inventory.collect_register.song_of_healing = 1;
      break;
    case 8:
      comData->save.inventory.collect_register.eponas_song = 1;
      break;
    case 9:
      comData->save.inventory.collect_register.song_of_soaring = 1;
      break;
    case 10:
      comData->save.inventory.collect_register.song_of_storms = 1;
      break;
    case 11:
      comData->save.inventory.collect_register.lullaby_intro = 1;
      break;
    default:
      break;
    }

    // give epona for Skip Epona Race setting
    // TODO: Skip shooting test.
    /*if (questBit == 14 && gSettingsContext.skipEponaRace == SKIP) {
        comData->eventChkInf[0x1] |= 0x0100;
        gSaveContext.horseData.pos.y = 0xF000; // place Epona OoB, so you can't reach her without
    playing the song
    }*/
  }

  void ItemEffect_PlaceMagicArrowsInInventory(game::CommonData* comData, s16 arg1, s16 arg2) {
    if (arg1 == 0) {  // Fairy Bow
      SaveFile_ResetItemSlotsIfMatchesID((u8)game::ItemId::FireArrow);
      SaveFile_ResetItemSlotsIfMatchesID((u8)game::ItemId::IceArrow);
      SaveFile_ResetItemSlotsIfMatchesID((u8)game::ItemId::LightArrow);
    } else if (game::HasItem(game::ItemId::Arrow)) {
      if (arg1 == 1 && !game::HasItem(game::ItemId::FireArrow)) {  // Fire Arrow
        game::GiveItem(game::ItemId::FireArrow);
      } else if (arg1 == 2 && !game::HasItem(game::ItemId::IceArrow)) {  // Ice Arrow
        game::GiveItem(game::ItemId::IceArrow);
      } else if (arg1 == 3 && !game::HasItem(game::ItemId::LightArrow)) {  // Light Arrow
        game::GiveItem(game::ItemId::LightArrow);
      }
    }
  }

  void ItemEffect_GiveUpgrade(game::CommonData* comData, s16 arg1, s16 arg2) {
    // This takes care of the item upgrade in inventory_count_register.
    util::GetPointer<void(u8, u8)>(0x023BF4C)(arg2, arg1);
    if (gSettingsContext.ammoDrops == (u8)AmmoDropsSetting::AMMODROPS_NONE) {
      switch (arg2) {
      // Arrows
      case 0:
        comData->save.inventory.item_counts[6] += 10;
        break;
      // Bombs
      case 1:
        comData->save.inventory.item_counts[11] += 10;
        break;
      // Deku Sticks
      case 6:
        comData->save.inventory.items[(u32)game::ItemId::DekuStick] = game::ItemId::DekuStick;
        comData->save.inventory.item_counts[13] += 10;
        break;
      // Deku Nuts
      case 7:
        comData->save.inventory.items[(u32)game::ItemId::DekuNuts] = game::ItemId::DekuNuts;
        comData->save.inventory.item_counts[14] += 10;
        break;
      }
    } else {
      switch (arg2) {
      case 0:
        comData->save.inventory.item_counts[6] = (20 + 10 * arg1);
        break;
      case 1:
        comData->save.inventory.item_counts[11] = (10 + 10 * arg1);
        break;
      case 6:
        comData->save.inventory.items[(u32)game::ItemId::DekuStick] = game::ItemId::DekuStick;
        comData->save.inventory.item_counts[13] = (10 * arg1);
        break;
      case 7:
        comData->save.inventory.items[(u32)game::ItemId::DekuNuts] = game::ItemId::DekuNuts;
        comData->save.inventory.item_counts[14] = (10 + 10 * arg1);
        break;
      }
    }
  }

  void ItemEffect_BeanPack(game::CommonData* comData, s16 arg1, s16 arg2) {
    game::GiveItem(game::ItemId::MagicBean);
    comData->save.inventory.item_counts[15] += 10;  // 10 Magic Beans
    return;
  }

  void ItemEffect_FillWalletUpgrade(game::CommonData* comData, s16 arg1, s16 arg2) {
    if (gSettingsContext.startingMaxRupees) {
      if (arg1 == 1) {
        comData->save.rupee_accumulator = 200;
      } else if (arg1 == 2) {
        comData->save.rupee_accumulator = 500;
      }
    }
  }

  void ItemEffect_GiveRemains(game::CommonData* comData, s16 mask, s16 arg2) {
    switch (mask) {
    case 0:
      comData->save.inventory.collect_register.odolwas_remains = 1;
    case 1:
      comData->save.inventory.collect_register.gohts_remains = 1;
    case 2:
      comData->save.inventory.collect_register.gyorgs_remains = 1;
    case 3:
      comData->save.inventory.collect_register.twinmolds_remains = 1;
    }
  }

  void ItemEffect_GiveDungeonItem(game::CommonData* comData, s16 mask, s16 dungeonId) {
    switch (dungeonId) {
    case 0:
      if (mask == 1)
        comData->save.inventory.woodfall_dungeon_items.boss_key = 1;
      else if (mask == 2)
        comData->save.inventory.woodfall_dungeon_items.compass = 1;
      else if (mask == 3)
        comData->save.inventory.woodfall_dungeon_items.map = 1;
      break;
    case 1:
      if (mask == 1)
        comData->save.inventory.snowhead_dungeon_items.boss_key = 1;
      else if (mask == 2)
        comData->save.inventory.snowhead_dungeon_items.compass = 1;
      else if (mask == 3)
        comData->save.inventory.snowhead_dungeon_items.map = 1;
      break;
    case 2:
      if (mask == 1)
        comData->save.inventory.great_bay_dungeon_items.boss_key = 1;
      else if (mask == 2)
        comData->save.inventory.great_bay_dungeon_items.compass = 1;
      else if (mask == 3)
        comData->save.inventory.great_bay_dungeon_items.map = 1;
      break;
    case 3:
      if (mask == 1)
        comData->save.inventory.stone_tower_dungeon_items.boss_key = 1;
      else if (mask == 2)
        comData->save.inventory.stone_tower_dungeon_items.compass = 1;
      else if (mask == 3)
        comData->save.inventory.stone_tower_dungeon_items.map = 1;
      break;
    }
  }

  void ItemEffect_GiveSkulltula(game::CommonData* comData, s16 whichHouse, s16 arg2) {
    switch (whichHouse) {
    case 0:
      comData->save.skulltulas_collected.swamp_count = comData->save.skulltulas_collected.swamp_count + 1;
      break;
    case 1:
      comData->save.skulltulas_collected.ocean_count = comData->save.skulltulas_collected.ocean_count + 1;
      break;
    default:
      break;
    }
  }

  void ItemEffect_GiveMask(game::CommonData* comData, s16 mask, s16 arg2) {
    switch (mask) {
    case 0:
      comData->save.inventory.collect_register.odolwas_remains = 1;
      break;
    case 1:
      comData->save.inventory.collect_register.gohts_remains = 1;
      break;
    case 2:
      comData->save.inventory.collect_register.gyorgs_remains = 1;
      break;
    case 3:
      comData->save.inventory.collect_register.twinmolds_remains = 1;
      break;
    }
    // Make this call as we need to update field_11 in Sub1 CommonData.
    rnd::util::GetPointer<void(game::GlobalContext*, int)>(0x222BCC)(rnd::GetContext().gctx, 0);
  }

}  // namespace rnd