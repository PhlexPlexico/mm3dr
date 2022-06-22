extern "C" {
#include <3ds/types.h>
}
#include "game/common_data.h"
#include "rnd/item_effect.h"
#include "rnd/razor_sword.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include <string.h>
#ifdef ENABLE_DEBUG
#include "common/debug.h"
#endif
//#define DECLARE_EXTSAVEDATA

namespace rnd {
  extern "C" void SaveFile_Init() {
    game::SaveData &saveData = game::GetCommonData().save;
#ifdef ENABLE_DEBUG
    //rnd::util::Print("%s: Made it to save debug values.", __func__);
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
    saveData.inventory.items[16] = game::ItemId::PowderKeg;

    saveData.inventory.masks[0] = game::ItemId::DekuMask;
    saveData.inventory.masks[1] = game::ItemId::GoronMask;
    saveData.inventory.masks[2] = game::ItemId::ZoraMask;
    saveData.inventory.masks[3] = game::ItemId::FierceDeityMask;
    saveData.inventory.masks[4] = game::ItemId::GibdoMask;
    saveData.inventory.masks[5] = game::ItemId::BunnyHood;
    saveData.inventory.masks[6] = game::ItemId::GaroMask;

    saveData.inventory.woodfall_temple_keys = 8;
    saveData.inventory.snowhead_temple_keys = 8;
    saveData.inventory.great_bay_temple_keys = 8;
    saveData.inventory.stone_tower_temple_keys = 8;
    saveData.inventory.woodfall_dungeon_items.map = 1;
    saveData.inventory.woodfall_dungeon_items.compass = 1;
    saveData.inventory.woodfall_dungeon_items.boss_key = 1;
    saveData.inventory.snowhead_dungeon_items.map = 1;
    saveData.inventory.snowhead_dungeon_items.compass = 1;
    saveData.inventory.snowhead_dungeon_items.boss_key = 1;
    saveData.inventory.great_bay_dungeon_items.map = 1;
    saveData.inventory.great_bay_dungeon_items.compass = 1;
    saveData.inventory.great_bay_dungeon_items.boss_key = 1;
    saveData.inventory.stone_tower_dungeon_items.map = 1;
    saveData.inventory.stone_tower_dungeon_items.compass = 1;
    saveData.inventory.stone_tower_dungeon_items.boss_key = 1;
    saveData.player.magic_acquired = 1; //Game does not check if value = 0, magic items still work
    saveData.player.magic_size_type = 2; //not init until saved?
    saveData.player.magic = 96;
    saveData.player.magic_num_upgrades = 1;
    saveData.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    saveData.inventory.item_counts[6] = 50;  // Arrows
    saveData.inventory.item_counts[11] = 40; // Bombs
    saveData.inventory.item_counts[12] = 40; // Bombchus
    saveData.inventory.item_counts[14] = 20; // Nuts
    saveData.inventory.item_counts[13] = 20; // Sticks
    saveData.has_great_spin_0x02 = 2;        // Set great spin.

    saveData.player.owl_statue_flags.great_bay = 1;
    saveData.player.owl_statue_flags.zora_cape = 1;
    saveData.player.owl_statue_flags.snowhead = 1;
    saveData.player.owl_statue_flags.mountain_village = 1;
    saveData.player.owl_statue_flags.clock_town = 1;
    saveData.player.owl_statue_flags.milk_road = 1;
    saveData.player.owl_statue_flags.woodfall = 1;
    saveData.player.owl_statue_flags.southern_swamp = 1;
    saveData.player.owl_statue_flags.ikana_canyon = 1;
    saveData.player.owl_statue_flags.stone_tower = 1;

    saveData.inventory.collect_register.sonata_of_awakening = 1;
    saveData.inventory.collect_register.goron_lullaby = 1;
    saveData.inventory.collect_register.new_wave_bossa_nova = 1;
    saveData.inventory.collect_register.elegy_of_emptiness = 1;
    saveData.inventory.collect_register.eponas_song = 1;
    saveData.inventory.collect_register.song_of_soaring = 1;
    saveData.inventory.collect_register.song_of_time = 1;

    //extra/temp testing items
    
#endif
    //TODO: Decomp event flags. Most likely in the large anonymous structs in the SaveData.
    u8 isNewFile = saveData.has_completed_intro;
    if (isNewFile == 0) {
      //TODO Time Savers:
      //Bomber's minigame skip ie. open hideout
      //Allow first time transformation to be skipable
      //Find flag for tatl dialogue at woodfall temple entrance platform
      //Find flag for tatl dialogue at snowhead entrance
      //Faster/skip dungeon unlock cutscene for swamp, mountain and zora
      //Fast songs works but needs to be applied to first time played too
      //skip Ikana king diolouge intro
      //skip pushing zora to shore
      //skip pirate leader diologue
      //Skip all giants cutscenes except for woodfall
      //Boss warp skipping the boss fight entirely

      //Skips cutscenes with no item checks attached
      //Also does not skip location access cutscenes like woodfall temple rise
      SaveFile_SkipMinorCutscenes();

      //OOT equivalent of starting with certain warp songs
      SaveFile_SetStartingOwlStatues(); //still needs to be fully added to options

      //Currently starting with ocarina and song of time is default in MM rando
      //These two items allows for skipping the first three day cycle
      saveData.inventory.collect_register.song_of_time = 1; //Part of starting equipment options
      saveData.inventory.items[0] = game::ItemId::Ocarina; //Part of starting quest items options
      //SaveFile_SetStartingInventory();

      saveData.has_tatl = true;
      saveData.has_completed_intro = 0x2B;
      saveData.ct_deku_flown_in_0x80_if_visited_once = 0x80;
      saveData.ct_deku_in_flower_0x04_if_present = 0x04;
      saveData.skip_tatl_talking_0x04 = 0x04;

      //This flag gets reset by song of time
      saveData.ct_guard_allows_through_if_0x30 = 0x30;

      //saveData.player.tatl_timer_maybe = 0x1000;
      saveData.player_form = game::act::Player::Form::Human;
    }
    
  }

  void SaveFile_SkipMinorCutscenes() {
    game::SaveData &saveData = game::GetCommonData().save;
    //addresses listed in comments is where it is in the savefile
    
    //Addresses 0x1250 to 0x1253
    //saveData.event_reg_maybe = 0xFE; as 1111 1110 in savefile
    //saveData.CutSceneFlagBundle1.unknown0 = 0;
    saveData.CutSceneFlagBundle1.termina_field = 1;
    saveData.CutSceneFlagBundle1.graveyard = 1;
    saveData.CutSceneFlagBundle1.romani_ranch = 1;
    saveData.CutSceneFlagBundle1.gorman_track = 1;
    saveData.CutSceneFlagBundle1.mountain_village = 1;
    saveData.CutSceneFlagBundle1.goron_city = 1;
    saveData.CutSceneFlagBundle1.snowhead = 1;

    //saveData.anonymous_69 = 0xFF;
    saveData.CutSceneFlagBundle1.southern_swamp = 1;
    saveData.CutSceneFlagBundle1.woodfall = 1;
    saveData.CutSceneFlagBundle1.deku_palace = 1;
    saveData.CutSceneFlagBundle1.great_bay_coast = 1;
    saveData.CutSceneFlagBundle1.pirates_fortress = 1;
    saveData.CutSceneFlagBundle1.zora_domain = 1;
    saveData.CutSceneFlagBundle1.waterfall_rapids = 1;
    saveData.CutSceneFlagBundle1.ikana_canyon = 1;

    //saveData.anonymous_70 = 0xFE; as 1111 1110 in savefile
    //saveData.CutSceneFlagBundle1.unknown16 = 0;
    saveData.CutSceneFlagBundle1.stone_tower = 1;
    saveData.CutSceneFlagBundle1.stone_tower_inverted = 1;
    saveData.CutSceneFlagBundle1.east_clock_town = 1;
    saveData.CutSceneFlagBundle1.west_clock_town = 1;
    saveData.CutSceneFlagBundle1.north_clock_town = 1;
    saveData.CutSceneFlagBundle1.woodfall_temple = 1;
    saveData.CutSceneFlagBundle1.snowhead_temple = 1;

    //saveData.gap1253 = 0x06; written as 0000 0110 in savefile
    //saveData.CutSceneFlagBundle1.unknown24 = 0;
    saveData.CutSceneFlagBundle1.stone_tower_temple = 1; 
    saveData.CutSceneFlagBundle1.stone_tower_temple_inverted = 1;  
    //saveData.CutSceneFlagBundle1.unknown27 = 0;
    //saveData.CutSceneFlagBundle1.unknown28 = 0;
    //saveData.CutSceneFlagBundle1.unknown29 = 0;
    //saveData.CutSceneFlagBundle1.unknown30 = 0;
    //saveData.CutSceneFlagBundle1.unknown31 = 0;
    
    //GreatbayTemple not in bundle above, does not seem to have a camera pan scene

    //ClockTown Owl statue: 0x12D3 = 0x10
    //saveData.anonymous_152_saved_once_0x10_sot_once_0x40 = 0x11;// 0x01 is deku palace
    saveData.CutSceneFlagBundle2.owl_statue_cut_scene = 1;
    //saveData.CutSceneFlagBundle2.unknown1 = 0;
    //saveData.CutSceneFlagBundle2.unknown2 = 0;
    //saveData.CutSceneFlagBundle2.unknown3 = 0;
    saveData.CutSceneFlagBundle2.deku_palace_throne_room_cutscene = 1;
    //saveData.CutSceneFlagBundle2.unknown5 = 0;
    //saveData.CutSceneFlagBundle2.unknown6 = 0;
    //saveData.CutSceneFlagBundle2.unknown7 = 0;

    //Meeting the Happy Mask Salesman: 
    //0x0EB4 = 0x01
    saveData.meeting_happy_mask_salesman_0x01 = 0x01;

    //SkullKid backstory cutscene:
    //0x07F4 = 0x10 
    saveData.skullkid_backstory_cutscene_0x10 = 0x10;

    //Road to Woodfall: 
    //0x12D9 = 0x08
    saveData.road_to_woodfall_camera_pan_0x08 = 0x08;
    
    //Pirate's fortress exterior:
    //0x09B5 = 0x04
    saveData.pirates_fortress_exterior_camera_pan_0x04 = 0x04;

    //Ikana Castle from canyon: 
    //0x05F4 = 0x08
    //saveData.gap249[931] = 0x08; //<- this gets rid of the Sunblock
    //0x05FB = 0x80
    saveData.ikana_castle_camera_pan_0x08 = 0x80;
  } 
  void SaveFile_SetStartingOwlStatues() {
      //future comfort option
      /*
      if(gSettingsContext.startingOwlStatues.ClockTown)
      saveData.player.owl_statue_flags.clock_town = 1;
      else if(gSettingsContext.startingOwlStatues.MilkRoad)
      saveData.player.owl_statue_flags.milk_road = 1;
      else if(gSettingsContext.startingOwlStatues.SouthernSwamp)
      saveData.player.owl_statue_flags.southern_swamp = 1;
      */
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
    game::SaveData &saveData = game::GetCommonData().save;
    //give maps and compasses
    if (gSettingsContext.mapsAndCompasses ==
        (u8)MapsAndCompassesSetting::MAPSANDCOMPASSES_START_WITH) {
      inventoryData.woodfall_dungeon_items.map = 1;
      inventoryData.woodfall_dungeon_items.compass = 1;
      inventoryData.snowhead_dungeon_items.map = 1;
      inventoryData.snowhead_dungeon_items.compass = 1;
      inventoryData.great_bay_dungeon_items.map = 1;
      inventoryData.great_bay_dungeon_items.compass = 1;
      inventoryData.stone_tower_dungeon_items.map = 1;
      inventoryData.stone_tower_dungeon_items.compass = 1;
    }
    
    //give small keys
    if (gSettingsContext.keysanity == (u8)KeysanitySetting::KEYSANITY_START_WITH) {
      inventoryData.woodfall_temple_keys = 1;
      inventoryData.snowhead_temple_keys = 3;
      inventoryData.great_bay_temple_keys = 3;
      inventoryData.stone_tower_temple_keys = 4;
      //give starting spirit keys for vanilla key locations
    }
    
    //give boss keys
    if (gSettingsContext.bossKeysanity == (u8)BossKeysanitySetting::BOSSKEYSANITY_START_WITH) {
      inventoryData.woodfall_dungeon_items.boss_key = 1;
      inventoryData.snowhead_dungeon_items.boss_key = 1;
      inventoryData.great_bay_dungeon_items.boss_key = 1;
      inventoryData.stone_tower_dungeon_items.boss_key = 1;
    }

    //starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
      inventoryData.items[9] = game::ItemId::DekuNuts;
      inventoryData.items[10] = game::ItemId::DekuStick;
      inventoryData.inventory_count_register.nut_upgrade = 0;
      inventoryData.inventory_count_register.stick_upgrades = 0;
    }

    //main inventory
    if (gSettingsContext.startingStickCapacity > 0) {
      inventoryData.items[10] = game::ItemId::DekuStick;
      inventoryData.inventory_count_register.stick_upgrades = 0;
      inventoryData.item_counts[13] = (gSettingsContext.startingStickCapacity + 1) * 10;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
      inventoryData.items[9] = game::ItemId::DekuNuts;
      inventoryData.inventory_count_register.nut_upgrade = 0;
      inventoryData.item_counts[14] = (gSettingsContext.startingNutCapacity + 1) * 10;
    }

    if (gSettingsContext.startingBombBag > 0) {
      inventoryData.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag20;
      inventoryData.items[6] = game::ItemId::Bomb;
      inventoryData.item_counts[11] = (gSettingsContext.startingBombBag + 1) * 10;
    }

    if (gSettingsContext.startingBombchus > 0) {
      inventoryData.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag20;
      inventoryData.items[7] = game::ItemId::Bombchu;
      inventoryData.item_counts[12] = 20;
    }

    if (gSettingsContext.startingHerosBow > 0) {
      inventoryData.items[1] = game::ItemId::Arrow;
      inventoryData.item_counts[6] = (gSettingsContext.startingHerosBow + 2) * 10;
    }

    if (gSettingsContext.startingFireArrows) {
      inventoryData.items[2] = game::ItemId::FireArrow;
    }

    if (gSettingsContext.startingIceArrows) {
      inventoryData.items[3] = game::ItemId::IceArrow;
    }

    if (gSettingsContext.startingLightArrows) {
      inventoryData.items[4] = game::ItemId::LightArrow;
    }

    if (gSettingsContext.startingLensOfTruth) {
      inventoryData.items[14] = game::ItemId::LensOfTruth;
    }

    if (gSettingsContext.startingMagicBean) {
      inventoryData.items[10] = game::ItemId::MagicBean;
      inventoryData.item_counts[15] = 10;
    }

    if (gSettingsContext.startingHookshot > 0) {
      inventoryData.items[15] = game::ItemId::Hookshot;
    }

    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle1, 0);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle2, 1);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle3, 2);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle4, 3);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle5, 4);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle6, 5);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle7, 6);

    if (gSettingsContext.startingOcarina > 0) {
      inventoryData.items[0] = game::ItemId::Ocarina;
    }

    if (gSettingsContext.startingGildedSword == (u8)StartingSwordSetting::STARTINGSWORD_GILDED) {
      equipmentData.sword_shield.sword = game::SwordType::GildedSword;
    }
    if (gSettingsContext.startingRazorSword == (u8)StartingSwordSetting::STARTINGSWORD_RAZOR) {
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
    if (gSettingsContext.startingDoubleDefense) {
      game::CommonData& cdata = game::GetCommonData();
      ItemEffect_GiveDefense(&cdata, 0, 0);
    }

    playerData.health_max = gSettingsContext.startingHealth << 4;
    playerData.health_current = gSettingsContext.startingHealth << 4;

    /*TODO - All these need to be broken up since we're not dealing with bitfields.
    // Quest items belong in the iventory array so we'll have to adjust which items we start with.
    // Use enums like everything else.
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

    // TODO: Starting stray fairies - need to update flags for which ones are acquired or not.
    if (gSettingsContext.startingSpinSettting == (u8)StartingSpinSetting::STARTINGSPIN_GREAT) {
        saveData.has_great_spin_0x02 = 2;
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
