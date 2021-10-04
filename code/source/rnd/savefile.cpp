extern "C" {
#include <3ds/types.h>
}
#include "game/common_data.h"
#include "rnd/item_effect.h"
#include "rnd/razor_sword.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include <string.h>
//#define DECLARE_EXTSAVEDATA

namespace rnd {
  extern "C" void SaveFile_Init(u32 fileBaseIndex) {
    game::SaveData &saveData = game::GetCommonData().save;
#ifdef ENABLE_DEBUG
    saveData.equipment.sword_shield.sword = game::SwordType::GildedSword;
    saveData.player.razor_sword_hp = 0x64;
    saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver50;
    saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag40;
    saveData.inventory.inventory_count_register.wallet_upgrade = 2;
    saveData.inventory.inventory_count_register.stick_upgrades = 2;
    saveData.inventory.inventory_count_register.nut_upgrade = 2;
    saveData.inventory.items[0] = game::ItemId::Ocarina;
    saveData.inventory.items[1] = game::ItemId::Arrow;
    saveData.inventory.items[2] = game::ItemId::FireArrow;
    saveData.inventory.items[3] = game::ItemId::IceArrow;
    saveData.inventory.items[4] = game::ItemId::LightArrow;
    saveData.inventory.items[6] = game::ItemId::Bomb;
    saveData.inventory.items[7] = game::ItemId::Bombchu;
    saveData.inventory.items[9] = game::ItemId::DekuNuts;
    saveData.inventory.items[10] = game::ItemId::DekuStick;
    saveData.inventory.items[13] = game::ItemId::PictographBox;
    saveData.inventory.items[15] = game::ItemId::Hookshot;
    
    saveData.inventory.woodfall_temple_keys = 8;
    saveData.inventory.snowhead_temple_keys = 8;
    saveData.inventory.great_bay_temple_keys = 8;
    saveData.inventory.stone_tower_temple_keys = 8;
    saveData.inventory.woodfall_boss_key = 1;
    saveData.inventory.snowhead_boss_key = 1;
    saveData.inventory.great_bay_boss_key = 1;
    saveData.inventory.stone_tower_boss_key = 1;
    saveData.player.magic_acquired = 1;
    saveData.player.magic_size_type = 1;
    saveData.player.magic = 96;
    saveData.player.magic_num_upgrades = 1;
    saveData.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    saveData.inventory.item_counts[6] = 50; // Arrows
    saveData.inventory.item_counts[11] = 20; // Bombs
    saveData.inventory.item_counts[12] = 20; // Bombchus
    saveData.inventory.item_counts[14] = 20; // Nuts
    saveData.inventory.item_counts[13] = 20; // Sticks
#endif
    //TODO: Decomp event flags. Most likely in the large anonymous structs in the SaveData.
    saveData.has_completed_intro = 1;
    saveData.inventory.collect_register.bombers_notebook = 1;
    //game::GiveItem(game::ItemId::BombersNotebook);
    //TODO: Things to set on
  }

    //Resolve the item ID for the starting bottle
  static void SaveFile_GiveStartingBottle(StartingBottleSetting startingBottle, u8 bottleSlot) {
    game::SaveData &saveData = game::GetCommonData().save;
    if (startingBottle > StartingBottleSetting::STARTINGBOTTLE_NONE) {
      saveData.inventory.bottles[bottleSlot] = (game::ItemId)startingBottle;
    }
  }

  u8 SaveFile_GetRemainsCount(void) {
    game::InventoryData &inventoryData = game::GetCommonData().save.inventory;
    u8 count = 0;

    count += inventoryData.collect_register.odolwas_remains ? 1 : 0;
    count += inventoryData.collect_register.gohts_remains ? 1 : 0;
    count += inventoryData.collect_register.gyorgs_remains ? 1 : 0;
    count += inventoryData.collect_register.twinmolds_remains ? 1 : 0;

    return count;
  }

  void SaveFile_SetStartingInventory(void) {
    game::InventoryData &inventoryData = game::GetCommonData().save.inventory;
    game::PlayerData &playerData = game::GetCommonData().save.player;
    game::EquipmentData &equipmentData = game::GetCommonData().save.equipment;
    //give maps and compasses
    /*if (gSettingsContext.mapsAndCompasses == MAPSANDCOMPASSES_START_WITH) {
      for (u8 i = 0; i < 0xA; i++) {
        gSaveContext.dungeonItems[i] |= 0x6;
      }
    }

    //give small keys
    if (gSettingsContext.keysanity == KEYSANITY_START_WITH) { //check if MQ dungeon               MQ : Vanilla key count
      gSaveContext.dungeonKeys[DUNGEON_FOREST_TEMPLE] = gSettingsContext.forestTempleDungeonMode ? 6 : 5;
      gSaveContext.dungeonKeys[DUNGEON_FIRE_TEMPLE] = gSettingsContext.fireTempleDungeonMode ? 5 : 8;
      gSaveContext.dungeonKeys[DUNGEON_WATER_TEMPLE] = gSettingsContext.waterTempleDungeonMode ? 2 : 6;
      gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE] = gSettingsContext.spiritTempleDungeonMode ? 7 : 5;
      gSaveContext.dungeonKeys[DUNGEON_SHADOW_TEMPLE] = gSettingsContext.shadowTempleDungeonMode ? 6 : 5;
      gSaveContext.dungeonKeys[DUNGEON_BOTTOM_OF_THE_WELL] = gSettingsContext.bottomOfTheWellDungeonMode ? 2 : 3;
      gSaveContext.dungeonKeys[DUNGEON_GERUDO_TRAINING_GROUNDS] = gSettingsContext.gerudoTrainingGroundsDungeonMode ? 3 : 9;
      gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] = gSettingsContext.ganonsCastleDungeonMode ? 3 : 2;
      //give starting spirit keys for vanilla key locations
    } else if (gSettingsContext.keysanity == KEYSANITY_VANILLA) {
      if (gSettingsContext.spiritTempleDungeonMode == DUNGEONMODE_MQ) {
        gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE] = 3;
      }
    }

    //give boss keys
    if (gSettingsContext.bossKeysanity == BOSSKEYSANITY_START_WITH) {
      for (u8 i = 3; i < 8; i++) {
        gSaveContext.dungeonItems[i] |= 0x1;
      }
    }

    //give Ganon's Castle Boss Key
    if (gSettingsContext.ganonsBossKey == GANONSBOSSKEY_START_WITH) {
      gSaveContext.dungeonItems[DUNGEON_GANONS_CASTLE_SECOND_PART] |= 0x1;
    }*/

    //starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
      game::GiveItem(game::ItemId::DekuNuts);
      game::GiveItem(game::ItemId::DekuStick);
      inventoryData.inventory_count_register.nut_upgrade = 0;
      inventoryData.inventory_count_register.stick_upgrades = 0;
    }

    //main inventory
    if (gSettingsContext.startingStickCapacity > 0) {
      game::GiveItem(game::ItemId::DekuStick);
      inventoryData.inventory_count_register.stick_upgrades = 0;
      inventoryData.item_counts[13] = (gSettingsContext.startingStickCapacity + 1) * 10;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
      game::GiveItem(game::ItemId::DekuNuts);
      inventoryData.inventory_count_register.nut_upgrade = 0;
      inventoryData.item_counts[14] = (gSettingsContext.startingNutCapacity + 1) * 10;
    }

    if (gSettingsContext.startingBombBag > 0) {
      game::GiveItem(game::ItemId::BombBag);
      game::GiveItem(game::ItemId::Bomb);
      inventoryData.item_counts[11] = (gSettingsContext.startingBombBag + 1) * 10;
    }

    if (gSettingsContext.startingBombchus > 0) {
      game::GiveItem(game::ItemId::Bombchu);
      inventoryData.item_counts[12] = 20;
    }

    if (gSettingsContext.startingHerosBow > 0) {
      game::GiveItem(game::ItemId::Arrow);
      inventoryData.item_counts[6] = (gSettingsContext.startingHerosBow + 2) * 10;
    }

    if (gSettingsContext.startingFireArrows) {
      game::GiveItem(game::ItemId::FireArrow);
    }

    if (gSettingsContext.startingIceArrows) {
      game::GiveItem(game::ItemId::IceArrow);
    }

    if (gSettingsContext.startingLightArrows) {
      game::GiveItem(game::ItemId::LightArrow);
    }

    if (gSettingsContext.startingLensOfTruth) {
      game::GiveItem(game::ItemId::LensOfTruth);
    }

    if (gSettingsContext.startingMagicBean) {
      game::GiveItem(game::ItemId::MagicBean);
      inventoryData.item_counts[15] = 10;
    }

    if (gSettingsContext.startingHookshot > 0) {
      game::GiveItem(game::ItemId::Hookshot);
    }

    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle1, 0);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle2, 1);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle3, 2);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle4, 3); 
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle5, 4); 
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle6, 5); 
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle7, 6); 

    if (gSettingsContext.startingOcarina > 0) {
      game::GiveItem(game::ItemId::Ocarina);
    }

    if (gSettingsContext.startingGildedSword == (u8)StartingSwordSetting::STARTINGSWORD_GILDED) {
      //game::GiveItem(game::ItemId::GildedSword);
      equipmentData.sword_shield.sword = game::SwordType::GildedSword;
    }
    if (gSettingsContext.startingRazorSword == (u8)StartingSwordSetting::STARTINGSWORD_RAZOR) {
      //game::GiveItem(game::ItemId::RazorSword);
      playerData.razor_sword_hp = RS_SetDurability();
      equipmentData.sword_shield.sword = game::SwordType::RazorSword;
    }

    if (gSettingsContext.startingMagicMeter == 1) {
      equipmentData.data[3].item_btns[0] = game::ItemId::DekuNuts;
      playerData.magic_size_type = 0;
      //playerData.magic_max_2 = 0;
      playerData.magic_num_upgrades = 0;
      playerData.magic_acquired = 1;
      playerData.magic = 0x30;
    } else if (gSettingsContext.startingMagicMeter == 2) {
      playerData.magic_size_type = 0;
      //playerData.magic_max_2 = 1;
      playerData.magic_num_upgrades = 1;
      playerData.magic_acquired = 1;
      playerData.magic = 0x60;
      equipmentData.data[3].item_btns[0] = game::ItemId::DekuNuts;
    }
    // TODO
    /*if (gSettingsContext.startingDoubleDefense) {
      ItemEffect_GiveDefense(&gSaveContext, 0, 0);
    }*/

    playerData.health_max = gSettingsContext.startingHealth << 4;
    playerData.health_current = gSettingsContext.startingHealth << 4;

/*TODO
    gSaveContext.questItems |= gSettingsContext.startingQuestItems;
    gSaveContext.questItems |= gSettingsContext.startingDungeonReward;
    gSaveContext.equipment |= gSettingsContext.startingEquipment;
    gSaveContext.upgrades |= gSettingsContext.startingUpgrades;
*/
    //max rupees
    if (gSettingsContext.startingMaxRupees) {
      u8 wallet = inventoryData.inventory_count_register.wallet_upgrade;
      if (wallet == 0) {
        playerData.rupee_count = 99;
      } else if (wallet == 1) {
        playerData.rupee_count = 200;
      } else if (wallet == 2) {
        playerData.rupee_count = 500;
      } else {
        playerData.rupee_count = 999;
      }
    }
  }

  void SaveFile_ResetItemSlotsIfMatchesID(u8 itemSlot) {
    game::SaveData &saveData = game::GetCommonData().save;
    // Remove the slot from child/adult grids
    for (u32 i = 0; i < 0x18; ++i) {
      if (saveData.inventory.items[i] == (game::ItemId)itemSlot) {
        saveData.inventory.items[i] = game::ItemId::None;
      }
    }
  }

}
