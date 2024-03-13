extern "C" {
#include <3ds/types.h>
}
#include <string.h>
#include "rnd/item_effect.h"
#include "rnd/item_table.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
#endif
#define DECLARE_EXTSAVEDATA
namespace rnd {
  ExtSaveData gExtSaveData;

  extern "C" void SaveFile_Init(game::GlobalContext* gctx, game::SaveFile* save) {
    game::SaveData& saveData = game::GetCommonData().save;
    game::CommonData& comData = game::GetCommonData();
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    rnd::util::Print("%s: Initing save file. Our save index is %u\nAre we a new file? %#04x\n", __func__,
                     comData.save_idx, saveData.has_completed_intro);
#endif
#ifdef ENABLE_DEBUG
    saveData.player.razor_sword_hp = 0x64;
    saveData.skulltulas_collected.swamp_count = 30;
    saveData.skulltulas_collected.ocean_count = 30;
    saveData.anonymous_162 = saveData.anonymous_162 | 0x6000;

    // rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::PowderKeg);
    // saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver50;
    saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag40;
    saveData.inventory.inventory_count_register.wallet_upgrade = 2;
    saveData.inventory.inventory_count_register.stick_upgrades = 2;
    saveData.inventory.inventory_count_register.nut_upgrade = 2;
    saveData.player.rupee_count = 5000;
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::Arrow);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::IceArrow);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::LightArrow);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::Bomb);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::Bombchu);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::DekuStick);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::DekuNuts);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::MagicBean);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::PowderKeg);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::LensOfTruth);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::Hookshot);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::PictographBox);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::LetterToMama);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::Bottle);

    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::DekuMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::GoronMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::ZoraMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::FierceDeityMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::MaskOfTruth);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::KafeiMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::AllNightMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::BunnyHood);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::KeatonMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::GaroMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::RomaniMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::CircusLeaderMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::PostmanHat);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::CoupleMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::GreatFairyMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::GibdoMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::DonGeroMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::KamaroMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::CaptainHat);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::StoneMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::BremenMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::BlastMask);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::MaskOfScents);
    rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::GiantMask);

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
    saveData.inventory.woodfall_fairies = 14;
    // saveData.player.magic_acquired = 1;   // Game does not check if value = 0, magic items still
    saveData.player.magic_size_type = 0;  // saveData.player.magic = 10;
    saveData.player.magic_num_upgrades = 0;
    saveData.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    saveData.inventory.item_counts[6] = 50;   // Arrows
    saveData.inventory.item_counts[11] = 40;  // Bombs
    saveData.inventory.item_counts[12] = 40;  // Bombchus
    saveData.inventory.item_counts[14] = 30;  // Nuts
    saveData.inventory.item_counts[13] = 20;  // Sticks
    saveData.has_great_spin_0x02 = 2;         // Set great spin.

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
    // saveData.inventory.collect_register.oath_to_order = 1;
    saveData.inventory.collect_register.song_of_healing = 1;

    gSettingsContext.skipBombersMinigame = 1;
    gSettingsContext.freeScarecrow = 1;
    saveData.activate_dungeon_skip_portal_0xF0_for_all = 0xF0;
    SaveFile_FillOverWorldMapData();
    saveData.inventory.collect_register.oath_to_order = 1;

    // Boss Remains
    saveData.inventory.collect_register.odolwas_remains = 1;
    saveData.inventory.collect_register.gohts_remains = 1;
    saveData.inventory.collect_register.gyorgs_remains = 1;
    saveData.inventory.collect_register.twinmolds_remains = 1;
#endif
    // TODO: Decomp event flags. Most likely in the large anonymous structs in the SaveData.
    u8 isNewFile = saveData.has_completed_intro;
    if (isNewFile == 0) {
      SaveFile_InitExtSaveData(comData.save_idx);
      saveData.has_tatl = true;
      // Skips cutscenes with no item checks attached
      // Also does not skip location access cutscenes like woodfall temple rise
      SaveFile_SkipMinorCutscenes();
      // Game has shorter animations for some events that were viewed at least once
      SaveFile_SetFastAnimationFlags();

      // OOT equivalent of starting with certain warp songs
      SaveFile_SetStartingOwlStatues();
      SaveFile_SetComfortOptions();

      /*Currently starting with ocarina and song of time is default in MM rando.
        These two items allows for skipping the first three day cycle.
        Currently there is no known way to get termina field to load
        in properly without ocarina in inventory.                                */
      saveData.inventory.collect_register.song_of_time = 1;  // Part of starting quest items options
      rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::Ocarina);
      // gSettingsContext.startingDekuMask = 1;  // start with Deku Mask, Song of Healing & Bomber's notebook always
      // saveData.inventory.collect_register.song_of_healing = 1;  // until happy mask salesman is overridden
      saveData.player.owl_statue_flags.clock_town = 1;
#ifdef ENABLE_DEBUG
      gSettingsContext.startingKokiriSword = 3;
      gSettingsContext.startingShield = 0;
#endif
      SaveFile_SetStartingInventory();

      // These events replay after song of time
      saveData.ct_guard_allows_through_if_0x20 = 0x20;
      saveData.tatl_dialogue_snowhead_entry_0x08 = 0x08;
      saveData.pirate_leader_dialogue_0x20 = 0x20;
      saveData.clock_town_temp_flags.ct_deku_in_flower_if_present = 1;
      saveData.skip_tingle_intro_dialogue_0x01 = 0x01;

      saveData.player_form = game::act::Player::Form::Human;
      // Shuffling now works, removing the starting item with notebook.
      // saveData.inventory.collect_register.bombers_notebook = 1;
    }
  }

  void SaveFile_SkipMinorCutscenes() {
    game::SaveData& saveData = game::GetCommonData().save;
    saveData.has_completed_intro = 0x2B;
    saveData.skip_tatl_talking_0x04 = 0x04;

    // camera panning cutscenes
    saveData.camera_panning_event_flag_bundle.termina_field = 1;
    saveData.camera_panning_event_flag_bundle.graveyard = 1;
    saveData.camera_panning_event_flag_bundle.romani_ranch = 1;
    saveData.camera_panning_event_flag_bundle.gorman_track = 1;
    saveData.camera_panning_event_flag_bundle.mountain_village = 1;
    saveData.camera_panning_event_flag_bundle.goron_city = 1;
    saveData.camera_panning_event_flag_bundle.snowhead = 1;
    saveData.camera_panning_event_flag_bundle.southern_swamp = 1;
    saveData.camera_panning_event_flag_bundle.woodfall = 1;
    saveData.camera_panning_event_flag_bundle.deku_palace = 1;
    saveData.camera_panning_event_flag_bundle.great_bay_coast = 1;
    saveData.camera_panning_event_flag_bundle.pirates_fortress_interior = 1;
    saveData.camera_panning_event_flag_bundle.zora_domain = 1;
    saveData.camera_panning_event_flag_bundle.waterfall_rapids = 1;
    saveData.camera_panning_event_flag_bundle.ikana_canyon = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower_inverted = 1;
    saveData.camera_panning_event_flag_bundle.east_clock_town = 1;
    saveData.camera_panning_event_flag_bundle.west_clock_town = 1;
    saveData.camera_panning_event_flag_bundle.north_clock_town = 1;
    saveData.camera_panning_event_flag_bundle.woodfall_temple = 1;
    saveData.camera_panning_event_flag_bundle.snowhead_temple_entry_room = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower_temple = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower_temple_inverted = 1;
    saveData.cut_scene_flag_bundle.deku_palace_throne_room_camera_pan = 1;
    saveData.road_to_woodfall_camera_pan_0x08 = 0x08;
    saveData.snowhead_temple_main_room_camera_pan_0x01 = 0x01;
    saveData.pirates_fortress_exterior_camera_pan_0x04 = 0x04;
    saveData.ikana_castle_camera_pan_0x08 = 0x80;

    // Tatl constant tatling skip
    saveData.cut_scene_flag_bundle.tatl_moon_tear_dialogue = 1;
    saveData.tatl_dialogue_flags2.go_south = 1;
    saveData.tatl_dialogue_direction_to_go.go_north = 1;
    saveData.tatl_dialogue_direction_to_go.go_west = 1;
    saveData.tatl_dialogue_direction_to_go.go_east = 1;
    saveData.tatl_dialogue_direction_to_go.go_to_skullkid = 1;
    saveData.woodfall_platform_tatl_dialogue_0x02 = 0x02;
    saveData.tatl_dialogue_inside_woodfall_temple_0x80 = 0x80;
    saveData.tatl_apology_dialogue_post_Odolwa_0x80 = 0x80;
    saveData.talt_dialogue_great_bay_temple.waterwheel_room_tatl_dialogue = 1;
    saveData.talt_dialogue_great_bay_temple.whirlpool_room_tatl_dialogue = 1;

    // tutorials
    // saveData.cut_scene_flag_bundle.map_tutorial_by_tingle = 1;

    // Misc cutscenes
    saveData.meeting_happy_mask_salesman_0x01 = 0x01;
    saveData.skullkid_backstory_cutscene_0x10 = 0x10;
    saveData.cut_scene_flag_bundle.owl_statue_cut_scene = 1;
    // saveData.dungeon_skip_portal_cutscene_0x3C_to_skip_all = 0x3C;
    saveData.turtle_flags.skip_swimming_to_great_bay_temple_cutscene = 1;

    // Needs to be greater than zero to skip first time song of time cutscene
    saveData.player.three_day_reset_count = 1;
  }

  void SaveFile_SetFastAnimationFlags() {
    game::SaveData& saveData = game::GetCommonData().save;
    // Masks
    saveData.have_worn_mask_once.has_worn_deku_mask_once = 1;
    saveData.have_worn_mask_once.has_worn_goron_mask_once = 1;
    saveData.have_worn_mask_once.has_worn_zora_mask_once = 1;
    saveData.have_worn_mask_once.has_worn_deity_mask_once = 1;
    // Dungeons
    saveData.opened_temple_once_flags.woodfall_temple_opened_at_least_once = 1;
    saveData.opened_temple_once_flags.snowhead_temple_opened_at_least_once = 1;
    saveData.opened_temple_once_flags.greatbay_temple_opened_at_least_once = 1;
    // Misc
    saveData.opened_temple_once_flags.deku_flown_in_at_least_once = 1;
  }

  void SaveFile_SetStartingOwlStatues() {
    game::SaveData& saveData = game::GetCommonData().save;
    // Walkable statues, could have an option to bundle this subgroup
    if (gSettingsContext.startingOwlStatues.clock_town)
      saveData.player.owl_statue_flags.clock_town = 1;
    if (gSettingsContext.startingOwlStatues.milk_road)
      saveData.player.owl_statue_flags.milk_road = 1;
    if (gSettingsContext.startingOwlStatues.southern_swamp)
      saveData.player.owl_statue_flags.southern_swamp = 1;
    // These give early location access
    if (gSettingsContext.startingOwlStatues.great_bay)
      saveData.player.owl_statue_flags.great_bay = 1;
    if (gSettingsContext.startingOwlStatues.zora_cape)
      saveData.player.owl_statue_flags.zora_cape = 1;
    if (gSettingsContext.startingOwlStatues.snowhead)
      saveData.player.owl_statue_flags.snowhead = 1;
    if (gSettingsContext.startingOwlStatues.mountain_village)
      saveData.player.owl_statue_flags.mountain_village = 1;
    if (gSettingsContext.startingOwlStatues.woodfall)
      saveData.player.owl_statue_flags.woodfall = 1;
    if (gSettingsContext.startingOwlStatues.ikana_canyon)
      saveData.player.owl_statue_flags.ikana_canyon = 1;
    if (gSettingsContext.startingOwlStatues.stone_tower)
      saveData.player.owl_statue_flags.stone_tower = 1;
  }

  void SaveFile_SetComfortOptions() {
    game::SaveData& saveData = game::GetCommonData().save;
    if (gSettingsContext.skipBombersMinigame) {
      // Not sure if bombers code is used elsewhere in the game's code
      saveData.bomberscode[0] = 0x01;
      saveData.bomberscode[1] = 0x02;
      saveData.bomberscode[2] = 0x03;
      saveData.bomberscode[3] = 0x04;
      saveData.bomberscode[4] = 0x05;
      saveData.clock_town_temp_flags.bomber_open_hideout = 1;  // Currently gets reset by Song of time
    }

    // Game uses an inventory check to determine whether you can
    // buy beans or powder kegs
    if (gSettingsContext.skipBeansTest) {
      // currently this will disable the free bean check
      // Instead bean daddy sells one bean for 10 rupees
      // saveData.inventory.items[10] = game::ItemId::MagicBean;
    }

    if (gSettingsContext.skipPowerKegTest) {
      // currently this will disable the PowerKegTest item check
      // Instead big goron sells one powder keg for 20 rupees
      // saveData.inventory.items[12] = game::ItemId::PowderKeg;
    }

    if (gSettingsContext.freeScarecrow) {
      // Currently sets song to the ingame default: LLLLLLLL
      saveData.inventory.collect_register.scarecrows_song_icon = 1;
      // both flags below get reset to 0 by song of time
      saveData.removes_scarecrow_from_shop_0x08 = 0x08;
      saveData.activate_scarecrow_song_0x01 = 0x01;
    }
  }

  void SaveFile_FillOverWorldMapData() {
    game::SaveData& saveData = game::GetCommonData().save;
    saveData.overworld_map_get_flags_0x3F_for_all = 0x3F;
    // setting individual maps is possible if necessary, the game just ||'s the map data in.
    // Currently sets data for all maps
    saveData.overworld_map_data[0] = 0x01;
    saveData.overworld_map_data[1] = 0x34;
    saveData.overworld_map_data[2] = 0xBF;
    saveData.overworld_map_data[3] = 0x72;
    saveData.overworld_map_data[4] = 0xBD;
    saveData.overworld_map_data[5] = 0xFB;
    saveData.overworld_map_data[6] = 0xBD;
    saveData.overworld_map_data[7] = 0x7B;
    saveData.overworld_map_data[8] = 0x6F;
    saveData.overworld_map_data[9] = 0xFD;
    saveData.overworld_map_data[10] = 0xFF;
    saveData.overworld_map_data[11] = 0x7F;
    saveData.overworld_map_data[12] = 0x0B;
    saveData.overworld_map_data[13] = 0xFD;
    saveData.overworld_map_data[14] = 0x07;
    gExtSaveData.tingleMaps.clock_town_map_get = 1;
    gExtSaveData.tingleMaps.great_bay_map_get = 1;
    gExtSaveData.tingleMaps.romani_map_get = 1;
    gExtSaveData.tingleMaps.snowhead_map_get = 1;
    gExtSaveData.tingleMaps.stone_tower_map_get = 1;
    gExtSaveData.tingleMaps.woodfall_map_get = 1;
  }

  // Resolve the item ID for the starting bottle
  static void SaveFile_GiveStartingBottle(StartingBottleSetting startingBottle, u8 bottleSlot) {
    game::SaveData& saveData = game::GetCommonData().save;
    if (startingBottle > StartingBottleSetting::STARTINGBOTTLE_NONE) {
      saveData.inventory.bottles[bottleSlot] = (game::ItemId)startingBottle;
    }
  }

  u8 SaveFile_GetRemainsCount(void) {
    game::SaveData& saveData = game::GetCommonData().save;
    u8 count = 0;

    count += saveData.inventory.collect_register.odolwas_remains ? 1 : 0;
    count += saveData.inventory.collect_register.gohts_remains ? 1 : 0;
    count += saveData.inventory.collect_register.gyorgs_remains ? 1 : 0;
    count += saveData.inventory.collect_register.twinmolds_remains ? 1 : 0;

    return count;
  }

  void SaveFile_SetStartingInventory(void) {
    game::PlayerData& playerData = game::GetCommonData().save.player;
    game::EquipmentData& equipmentData = game::GetCommonData().save.equipment;
    // game::SaveData& saveBackupData = game::GetCommonData().save_backup;
    game::SaveData& saveData = game::GetCommonData().save;
    // give maps and compasses
    if (gSettingsContext.mapsAndCompasses == (u8)MapsAndCompassesSetting::MAPSANDCOMPASSES_START_WITH) {
      saveData.inventory.woodfall_dungeon_items.map = 1;
      saveData.inventory.woodfall_dungeon_items.compass = 1;
      saveData.inventory.snowhead_dungeon_items.map = 1;
      saveData.inventory.snowhead_dungeon_items.compass = 1;
      saveData.inventory.great_bay_dungeon_items.map = 1;
      saveData.inventory.great_bay_dungeon_items.compass = 1;
      saveData.inventory.stone_tower_dungeon_items.map = 1;
      saveData.inventory.stone_tower_dungeon_items.compass = 1;
    }

    // give small keys
    if (gSettingsContext.keysanity == (u8)KeysanitySetting::KEYSANITY_START_WITH) {
      saveData.inventory.woodfall_temple_keys = 1;
      saveData.inventory.snowhead_temple_keys = 3;
      saveData.inventory.great_bay_temple_keys = 3;
      saveData.inventory.stone_tower_temple_keys = 4;
      // give starting spirit keys for vanilla key locations
    } else {
      // Init to 0 as the game inits to 255.
      saveData.inventory.woodfall_temple_keys = 0;
      saveData.inventory.snowhead_temple_keys = 0;
      saveData.inventory.great_bay_temple_keys = 0;
      saveData.inventory.stone_tower_temple_keys = 0;
#ifdef ENABLE_DEBUG
      saveData.inventory.woodfall_temple_keys = 8;
      saveData.inventory.snowhead_temple_keys = 8;
      saveData.inventory.great_bay_temple_keys = 8;
      saveData.inventory.stone_tower_temple_keys = 8;
#endif
    }

    // give boss keys
    if (gSettingsContext.bossKeysanity == (u8)BossKeysanitySetting::BOSSKEYSANITY_START_WITH) {
      saveData.inventory.woodfall_dungeon_items.boss_key = 1;
      saveData.inventory.snowhead_dungeon_items.boss_key = 1;
      saveData.inventory.great_bay_dungeon_items.boss_key = 1;
      saveData.inventory.stone_tower_dungeon_items.boss_key = 1;
    }

    // starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
      saveData.inventory.items[9] = game::ItemId::DekuNuts;
      saveData.inventory.items[8] = game::ItemId::DekuStick;
      saveData.inventory.inventory_count_register.nut_upgrade = 1;
      saveData.inventory.inventory_count_register.stick_upgrades = 1;
      saveData.inventory.item_counts[13] = 10;
      saveData.inventory.item_counts[14] = 20;
    }

    // main inventory
    if (gSettingsContext.startingStickCapacity > 0) {
      saveData.inventory.items[8] = game::ItemId::DekuStick;
      saveData.inventory.inventory_count_register.stick_upgrades = gSettingsContext.startingStickCapacity;
      saveData.inventory.item_counts[13] = (gSettingsContext.startingStickCapacity) * 10;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
      saveData.inventory.items[9] = game::ItemId::DekuNuts;
      saveData.inventory.inventory_count_register.nut_upgrade = gSettingsContext.startingNutCapacity;
      saveData.inventory.item_counts[14] = (gSettingsContext.startingNutCapacity + 1) * 10;
    }

    if (gSettingsContext.startingBombBag > 0) {
      saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag20;
      saveData.inventory.items[6] = game::ItemId::Bomb;
      saveData.inventory.item_counts[11] = (gSettingsContext.startingBombBag + 1) * 10;
    } else if (gSettingsContext.startingBombBag > 1) {
      saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag30;
      saveData.inventory.items[6] = game::ItemId::Bomb;
      saveData.inventory.item_counts[11] = (gSettingsContext.startingBombBag + 1) * 10;
    } else if (gSettingsContext.startingBombBag > 2) {
      saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag40;
      saveData.inventory.items[6] = game::ItemId::Bomb;
      saveData.inventory.item_counts[11] = (gSettingsContext.startingBombBag + 1) * 10;
    } else {
      saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::NoBag;
    }

    if (gSettingsContext.startingBombchus > 0) {
      saveData.inventory.items[7] = game::ItemId::Bombchu;
      saveData.inventory.item_counts[12] = 20;
    }

    if (gSettingsContext.startingHerosBow > 0) {
      saveData.inventory.items[1] = game::ItemId::Arrow;
      saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver30;
      saveData.inventory.item_counts[6] = (gSettingsContext.startingHerosBow + 2) * 10;
    } else if (gSettingsContext.startingHerosBow > 1) {
      saveData.inventory.items[1] = game::ItemId::Arrow;
      saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver40;
      saveData.inventory.item_counts[6] = (gSettingsContext.startingHerosBow + 2) * 10;
    } else if (gSettingsContext.startingHerosBow > 2) {
      saveData.inventory.items[1] = game::ItemId::Arrow;
      saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver50;
      saveData.inventory.item_counts[6] = (gSettingsContext.startingHerosBow + 2) * 10;
    } else {
      saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::NoQuiver;
#ifdef ENABLE_DEBUG
      saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver50;
      // rnd::util::GetPointer<void(game::ItemId, int)>(0x21d440)(game::ItemId::Arrow, 0x1e);
#endif
    }

    if (gSettingsContext.startingFireArrows) {
      saveData.inventory.items[2] = game::ItemId::FireArrow;
    }

    if (gSettingsContext.startingIceArrows) {
      saveData.inventory.items[3] = game::ItemId::IceArrow;
    }

    if (gSettingsContext.startingLightArrows) {
      saveData.inventory.items[4] = game::ItemId::LightArrow;
    }

    if (gSettingsContext.startingLensOfTruth) {
      saveData.inventory.items[14] = game::ItemId::LensOfTruth;
    }

    if (gSettingsContext.startingMagicBean) {
      saveData.inventory.items[10] = game::ItemId::MagicBean;
      saveData.inventory.item_counts[15] = 10;
    }

    if (gSettingsContext.startingHookshot > 0) {
      saveData.inventory.items[15] = game::ItemId::Hookshot;
    }

    if (gSettingsContext.startingPowderKeg > 0) {
      saveData.inventory.items[12] = game::ItemId::PowderKeg;
    }

    if (gSettingsContext.startingPictographBox > 0) {
      rnd::util::GetPointer<void(game::ItemId)>(0x22b14c)(game::ItemId::PictographBox);
      saveData.inventory.items[13] = game::ItemId::PictographBox;
    }

    if (gSettingsContext.startingGreatFairySword > 0) {
      saveData.inventory.items[16] = game::ItemId::GreatFairySword;
    }

    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle1, 0);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle2, 1);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle3, 2);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle4, 3);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle5, 4);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle6, 5);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle7, 6);

    if (gSettingsContext.startingOcarina > 0) {
      saveData.inventory.items[0] = game::ItemId::Ocarina;
    }

    if (gSettingsContext.startingWallet == (u8)StartingWalletSetting::STARTINGWALLET_NONE) {
      saveData.inventory.inventory_count_register.wallet_upgrade = 0;  // might not be needed?
    } else if (gSettingsContext.startingWallet == (u8)StartingWalletSetting::STARTINGWALLET_ADULT) {
      saveData.inventory.inventory_count_register.wallet_upgrade = 1;
    } else if (gSettingsContext.startingWallet == (u8)StartingWalletSetting::STARTINGWALLET_GIANT) {
      saveData.inventory.inventory_count_register.wallet_upgrade = 2;
    } else if (gSettingsContext.startingWallet == (u8)StartingWalletSetting::STARTINGWALLET_TYCOON) {
      saveData.inventory.inventory_count_register.wallet_upgrade = 2;  // 2 for now until tycoon is added
    }
    if (gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_NONE) {
      equipmentData.sword_shield.sword = game::SwordType::NoSword;
      saveData.equipment.data[0].item_btn_b = game::ItemId::None;
    } else if (gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_KOKIRI) {
      equipmentData.sword_shield.sword = game::SwordType::KokiriSword;
      saveData.equipment.data[0].item_btn_b = game::ItemId::KokiriSword;
    } else if (gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_RAZOR) {
      equipmentData.sword_shield.sword = game::SwordType::RazorSword;
      saveData.equipment.data[0].item_btn_b = game::ItemId::RazorSword;
    } else if (gSettingsContext.startingKokiriSword == (u8)StartingSwordSetting::STARTINGSWORD_GILDED) {
      equipmentData.sword_shield.sword = game::SwordType::GildedSword;
      saveData.equipment.data[0].item_btn_b = game::ItemId::GildedSword;
    }

    if (gSettingsContext.shuffleStartingShield) {
      equipmentData.sword_shield.shield = game::ShieldType::NoShield;
    } else if (gSettingsContext.startingShield == (u8)StartingSheildSetting::STARTINGSHIELD_NONE) {
      equipmentData.sword_shield.shield = game::ShieldType::NoShield;
    } else if (gSettingsContext.startingShield == (u8)StartingSheildSetting::STARTINGSHIELD_HERO) {
      equipmentData.sword_shield.shield = game::ShieldType::HeroShield;
    } else if (gSettingsContext.startingShield == (u8)StartingSheildSetting::STARTINGSHIELD_MIRROR) {
      equipmentData.sword_shield.shield = game::ShieldType::MirrorShield;
    }

    // Masks

    if (gSettingsContext.startingPostmanHat > 0) {
      saveData.inventory.masks[0] = game::ItemId::PostmanHat;
    }

    if (gSettingsContext.startingAllNightMask > 0) {
      saveData.inventory.masks[1] = game::ItemId::AllNightMask;
    }

    if (gSettingsContext.startingStoneMask > 0) {
      saveData.inventory.masks[3] = game::ItemId::StoneMask;
    }

    if (gSettingsContext.startingBlastMask > 0) {
      saveData.inventory.masks[2] = game::ItemId::BlastMask;
    }

    if (gSettingsContext.startingGreatFairyMask > 0) {
      saveData.inventory.masks[4] = game::ItemId::GreatFairyMask;
    }

    if (gSettingsContext.startingDekuMask > 0) {
      saveData.inventory.masks[5] = game::ItemId::DekuMask;
    }

    if (gSettingsContext.startingKeatonMask > 0) {
      saveData.inventory.masks[6] = game::ItemId::KeatonMask;
    }

    if (gSettingsContext.startingBremenMask > 0) {
      saveData.inventory.masks[7] = game::ItemId::BremenMask;
    }

    if (gSettingsContext.startingBunnyHood > 0) {
      saveData.inventory.masks[8] = game::ItemId::BunnyHood;
    }

    if (gSettingsContext.startingDonGerosMask > 0) {
      saveData.inventory.masks[9] = game::ItemId::DonGeroMask;
    }

    if (gSettingsContext.startingMaskOfScents > 0) {
      saveData.inventory.masks[10] = game::ItemId::MaskOfScents;
    }

    if (gSettingsContext.startingGoronMask > 0) {
      saveData.inventory.masks[11] = game::ItemId::GoronMask;
    }

    if (gSettingsContext.startingRomanisMask > 0) {
      saveData.inventory.masks[12] = game::ItemId::RomaniMask;
    }

    if (gSettingsContext.startingCircusLeadersMask > 0) {
      saveData.inventory.masks[13] = game::ItemId::CircusLeaderMask;
    }

    if (gSettingsContext.startingKafeiMask > 0) {
      saveData.inventory.masks[14] = game::ItemId::KafeiMask;
    }

    if (gSettingsContext.startingCouplesMask > 0) {
      saveData.inventory.masks[15] = game::ItemId::CoupleMask;
    }

    if (gSettingsContext.startingMaskOfTruth > 0) {
      saveData.inventory.masks[16] = game::ItemId::MaskOfTruth;
    }

    if (gSettingsContext.startingZoraMask > 0) {
      saveData.inventory.masks[17] = game::ItemId::ZoraMask;
    }

    if (gSettingsContext.startingKamarosMask > 0) {
      saveData.inventory.masks[18] = game::ItemId::KamaroMask;
    }

    if (gSettingsContext.startingGibdosMask > 0) {
      saveData.inventory.masks[19] = game::ItemId::GibdoMask;
    }

    if (gSettingsContext.startingGaroMask > 0) {
      saveData.inventory.masks[20] = game::ItemId::GaroMask;
    }

    if (gSettingsContext.startingCaptainsHat > 0) {
      saveData.inventory.masks[21] = game::ItemId::CaptainHat;
    }

    if (gSettingsContext.startingGiantsMask > 0) {
      saveData.inventory.masks[22] = game::ItemId::GiantMask;
    }

    if (gSettingsContext.startingFierceDeityMask > 0) {
      saveData.inventory.masks[23] = game::ItemId::FierceDeityMask;
    }

    // Songs

    if (gSettingsContext.startingSongOfHealing > 0) {
      saveData.inventory.collect_register.song_of_healing = 1;
    }

    if (gSettingsContext.startingSongOfSoaring > 0) {
      saveData.inventory.collect_register.song_of_soaring = 1;
    }

    if (gSettingsContext.startingSonataOfAwakening > 0) {
      saveData.inventory.collect_register.sonata_of_awakening = 1;
    }

    if (gSettingsContext.startingGoronsLullaby > 0) {
      saveData.inventory.collect_register.goron_lullaby = 1;
    }

    if (gSettingsContext.startingNewWaveBossaNova > 0) {
      saveData.inventory.collect_register.new_wave_bossa_nova = 1;
    }

    if (gSettingsContext.startingElegyOfEmptiness > 0) {
      saveData.inventory.collect_register.elegy_of_emptiness = 1;
    }

    if (gSettingsContext.startingEponasSong > 0) {
      saveData.inventory.collect_register.eponas_song = 1;
    }

    if (gSettingsContext.startingSongOfStorms > 0) {
      saveData.inventory.collect_register.song_of_storms = 1;
    }

    if (gSettingsContext.startingOathToOrder > 0) {
      saveData.inventory.collect_register.oath_to_order = 1;
    }

    // Boss Remains
    if (gSettingsContext.startingOdolwaRemains > 0) {
      saveData.inventory.collect_register.odolwas_remains = 1;
    }

    if (gSettingsContext.startingGohtRemains > 0) {
      saveData.inventory.collect_register.gohts_remains = 1;
    }

    if (gSettingsContext.startingGyorgRemains > 0) {
      saveData.inventory.collect_register.gyorgs_remains = 1;
    }

    if (gSettingsContext.startingTwinmoldRemains > 0) {
      saveData.inventory.collect_register.twinmolds_remains = 1;
    }

    if (gSettingsContext.startingMagicMeter == 1) {
      equipmentData.data[3].item_btns[0] = game::ItemId::DekuNuts;
      playerData.magic_size_type = 1;
      // playerData.magic_max_2 = 0;
      playerData.magic_num_upgrades = 0;
      playerData.magic_acquired = 1;
      playerData.magic = 0x30;
    } else if (gSettingsContext.startingMagicMeter == 2) {
      playerData.magic_size_type = 2;
      // playerData.magic_max_2 = 1;
      playerData.magic_num_upgrades = 1;
      playerData.magic_acquired = 1;
      playerData.magic = 0x60;
      equipmentData.data[3].item_btns[0] = game::ItemId::DekuNuts;
    } else {
      // Player initially is given magic 0x30 on save creation. This prevents that.
      playerData.magic = 0x0;
      playerData.magic_acquired = 0;
#ifdef ENABLE_DEBUG
      playerData.magic = 0x30;
#endif
    }

    if (gSettingsContext.startingDoubleDefense) {
      playerData.double_defense = 1;
    }

#ifdef ENABLE_DEBUG
    playerData.health_max = 16 << 4;
    playerData.health_current = 16 << 4;
#else
    if (SaveFile_IsValidSettingsHealth()) {
      playerData.health_max = gSettingsContext.startingHealth << 4;
      playerData.health_current = gSettingsContext.startingHealth << 4;
    } else {
      playerData.health_max = 3 << 4;
      playerData.health_current = 3 << 4;
    }

#endif

    /*TODO - All these need to be broken up since we're not dealing with bitfields.
    // Quest items belong in the iventory array so we'll have to adjust which items we start with.
    // Use enums like everything else.
    gSaveContext.questItems |= gSettingsContext.startingQuestItems;
    gSaveContext.questItems |= gSettingsContext.startingDungeonReward;
    gSaveContext.equipment |= gSettingsContext.startingEquipment;
    gSaveContext.upgrades |= gSettingsContext.startingUpgrades;
*/
    // max rupees
    if (gSettingsContext.startingMaxRupees) {
      u8 wallet = saveData.inventory.inventory_count_register.wallet_upgrade;
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
    game::SaveData& saveData = game::GetCommonData().save;
    // Remove the slot from child/adult grids
    for (u32 i = 0; i < 0x18; ++i) {
      if (saveData.inventory.items[i] == (game::ItemId)itemSlot) {
        saveData.inventory.items[i] = game::ItemId::None;
      }
    }
  }

  bool SaveFile_IsValidSettingsHealth() {
    if (gSettingsContext.startingHealth <= 0) {
      return false;
    }
    return true;
  }

  void SaveFile_InitExtSaveData(u32 saveNumber) {
    gExtSaveData.version = EXTSAVEDATA_VERSION;  // Do not change this line
    gExtSaveData.isNewFile = 1;
    // TODO: BitField for event flags instead?
    // memset(&gExtSaveData.extInf, 0, sizeof(gExtSaveData.extInf));
    gExtSaveData.givenItemChecks.raw = 0;
    gExtSaveData.fairyRewards.raw = 0;
    gExtSaveData.tingleMaps.raw = 0;
    gExtSaveData.playtimeSeconds = 0;
    memset(&gExtSaveData.chestRewarded, 0, sizeof(gExtSaveData.chestRewarded));
    memset(&gExtSaveData.scenesDiscovered, 0, sizeof(gExtSaveData.scenesDiscovered));
    memset(&gExtSaveData.itemCollected, 0, sizeof(gExtSaveData.itemCollected));
#ifdef ENABLE_DEBUG
    gExtSaveData.collectedTradeItems[0] = game::ItemId::MoonTear;
    gExtSaveData.collectedTradeItems[1] = game::ItemId::LandTitleDeed;
    gExtSaveData.collectedTradeItems[2] = game::ItemId::SwampTitleDeed;
    gExtSaveData.collectedTradeItems[3] = game::ItemId::MountainTitleDeed;
    gExtSaveData.collectedTradeItems[4] = game::ItemId::OceanTitleDeed;
    gExtSaveData.collectedTradeItems[5] = game::ItemId::RoomKey;
    gExtSaveData.collectedTradeItems[6] = game::ItemId::LetterToKafei;
    gExtSaveData.collectedTradeItems[7] = game::ItemId::PendantOfMemories;
    gExtSaveData.collectedTradeItems[8] = game::ItemId::LetterToMama;
#else
    for (int i = 0; i < 9; i++) {
      gExtSaveData.collectedTradeItems[i] = game::ItemId::None;
    }
#endif

    // TODO: Settings options belong in ext.
    // memset(&gExtSaveData.entrancesDiscovered, 0, sizeof(gExtSaveData.entrancesDiscovered));
    // // Ingame Options
    // gExtSaveData.option_EnableBGM          = gSettingsContext.playMusic;
    // gExtSaveData.option_EnableSFX          = gSettingsContext.playSFX;
    // gExtSaveData.option_SilenceNavi        = gSettingsContext.silenceNavi;
    // gExtSaveData.option_IgnoreMaskReaction = gSettingsContext.ignoreMaskReaction;
    // gExtSaveData.option_SkipSongReplays    = gSettingsContext.skipSongReplays;
  }

  u8 SaveFile_GetIsSceneDiscovered(u8 sceneNum) {
    u32 numBits = sizeof(u32) * 8;
    u32 idx = sceneNum / numBits;
    if (idx < SAVEFILE_SCENES_DISCOVERED_IDX_COUNT) {
      u32 bit = 1 << (sceneNum - (idx * numBits));
      return (gExtSaveData.scenesDiscovered[idx] & bit) != 0;
    }
    return 0;
  }

  void SaveFile_SetSceneDiscovered(u16 sceneNum) {
    if (SaveFile_GetIsSceneDiscovered(sceneNum)) {
      return;
    }

    u16 numBits = sizeof(u32) * 8;
    u32 idx = sceneNum / numBits;
    if (idx < SAVEFILE_SCENES_DISCOVERED_IDX_COUNT) {
      u32 sceneBit = 1 << (sceneNum - (idx * numBits));
      gExtSaveData.scenesDiscovered[idx] |= sceneBit;
    }
  }

  extern "C" void SaveFile_LoadExtSaveData() {
    char path[] = "/0.bin";
    u32 version;
    u64 fileSize;
    u32 newSave;
    u16 saveNumber = game::GetCommonData().save_idx;
    Result res;
    FS_Archive fsa;
    Handle fileHandle = extInitFileHandle();
    if (R_FAILED(res = extDataMount(&fsa))) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
      rnd::util::Print("%s: Failed to mount ext data.\n", __func__);
#endif
      SaveFile_InitExtSaveData(saveNumber);
      SaveFile_SaveExtSaveData();
      return;
    }

    path[1] = saveNumber + '0';

    // Load default values if the file does not exist
    if (R_FAILED(res = extDataOpen(&fileHandle, fsa, path))) {
      extDataUnmount(fsa);
      SaveFile_InitExtSaveData(saveNumber);
      SaveFile_SaveExtSaveData();
      return;
    }

    // Delete the file and load default values if the size does not match or the version is
    // different
    FSFILE_GetSize(fileHandle, &fileSize);
    extDataReadFile(fileHandle, &version, 0, sizeof(version));
    extDataReadFile(fileHandle, &newSave, 8, sizeof(newSave));
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    util::Print("%s: Is New file? %u\n", __func__, newSave);
#endif
    if (fileSize != sizeof(gExtSaveData) || version != EXTSAVEDATA_VERSION || gExtSaveData.isNewFile == 1) {
      extDataClose(fileHandle);
      extDataDeleteFile(fsa, path);
      SaveFile_InitExtSaveData(saveNumber);
      gExtSaveData.isNewFile = 0;
      extDataWriteFileDirectly(fsa, path, &gExtSaveData, 0, sizeof(gExtSaveData));
      extDataUnmount(fsa);
      return;
    }

    extDataReadFile(fileHandle, &gExtSaveData, 0, sizeof(gExtSaveData));

    extDataUnmount(fsa);
    extDataClose(fileHandle);
  }

  extern "C" void SaveFile_SaveExtSaveData() {
    game::CommonData& comData = game::GetCommonData();
    char path[] = "/0.bin";

    Result res;
    FS_Archive fsa;
    extInitFileHandle();
    if (R_FAILED(res = extDataMount(&fsa))) {
      return;
    }

    path[1] = comData.save_idx + '0';

    extDataWriteFileDirectly(fsa, path, &gExtSaveData, 0, sizeof(gExtSaveData));
    extDataUnmount(fsa);
  }

  extern "C" void SaveFile_RemoveStoredTradeItem(u16 item, u8 slot) {
#if defined ENABLE_DEBUG
    return;
#endif
    // This is a get item ID, we need to translate it to the regular item ID.
    if (slot != 5 && slot != 17)
      return;
    ItemRow* gidItemRow = ItemTable_GetItemRowFromIndex(item);
    game::ItemId firstItem = game::ItemId::None;

    for (int i = 0; i < 9; i++) {
      if (gidItemRow->itemId != (u8)gExtSaveData.collectedTradeItems[i] && firstItem == game::ItemId::None) {
        if (slot == 17 && i > 5 && i < 8) {
          firstItem = gExtSaveData.collectedTradeItems[i];
        }

        else if (slot == 5 && i < 5)
          firstItem = gExtSaveData.collectedTradeItems[i];
      }
      if (gidItemRow->itemId == (u8)gExtSaveData.collectedTradeItems[i]) {
        gExtSaveData.collectedTradeItems[i] = game::ItemId::None;
      }
    }
    // Place the item in inventory, if there is no item to place it simply places none.
    game::SaveData& saveData = game::GetCommonData().save;
    saveData.inventory.items[slot] = firstItem;
  }
  extern "C" void SaveFile_RemoveTradeItemFromSlot(u16 item, u8 slot) {
#if defined ENABLE_DEBUG
    return;
#endif
    if (slot == 5) {
      for (int i = 0; i < 5; i++) {
        if (item == (u16)gExtSaveData.collectedTradeItems[i]) {
          gExtSaveData.collectedTradeItems[i] = game::ItemId::None;
          break;
        }
      }
    } else if (slot == 17 && item == (u16)game::ItemId::LetterToKafei) {
      gExtSaveData.collectedTradeItems[6] = game::ItemId::None;
    }
  }

  extern "C" u8 SaveFile_GetItemCurrentlyInSlot(u8 slot) {
    if (game::GetCommonData().save.inventory.items[slot] == game::ItemId::MysteryMilk) {
      gExtSaveData.givenItemChecks.bottleMysteryGivenToEnGm = 1;
    }
    return (u8)game::GetCommonData().save.inventory.items[slot];
  }

  extern "C" void SaveFile_SetNextTradeSlotItem(u8 slot) {
    if (slot != 5 && slot != 17)
      return;
    game::ItemId firstItem = game::ItemId::None;
    for (int i = 0; i < 9; i++) {
      if (firstItem == game::ItemId::None) {
        if (slot == 17 && i > 5 && i < 8 && gExtSaveData.collectedTradeItems[i] != game::ItemId::None) {
          firstItem = gExtSaveData.collectedTradeItems[i];
          break;
        } else if (slot == 5 && i < 5 && gExtSaveData.collectedTradeItems[i] != game::ItemId::None) {
          firstItem = gExtSaveData.collectedTradeItems[i];
          break;
        }
      }
    }
    // Place the item in inventory, if there is no item to place it simply places none.
    game::SaveData& saveData = game::GetCommonData().save;
    saveData.inventory.items[slot] = firstItem;
  }
  // SaveFile_DrawAndShowUIMessage() {

  // }

  extern "C" u16 CurrentMasksInInventory() {
    // I can see why the original devs did this, because they did not want to count specific masks (transform + FD)
    u16 count = 0;
    if (game::HasMask(game::ItemId::MaskOfTruth))
      count += 1;
    if (game::HasMask(game::ItemId::KafeiMask))
      count += 1;
    if (game::HasMask(game::ItemId::AllNightMask))
      count += 1;
    if (game::HasMask(game::ItemId::BunnyHood))
      count += 1;
    if (game::HasMask(game::ItemId::KeatonMask))
      count += 1;
    if (game::HasMask(game::ItemId::GaroMask))
      count += 1;
    if (game::HasMask(game::ItemId::RomaniMask))
      count += 1;
    if (game::HasMask(game::ItemId::CircusLeaderMask))
      count += 1;
    if (game::HasMask(game::ItemId::PostmanHat))
      count += 1;
    if (game::HasMask(game::ItemId::CoupleMask))
      count += 1;
    if (game::HasMask(game::ItemId::GreatFairyMask))
      count += 1;
    if (game::HasMask(game::ItemId::GibdoMask))
      count += 1;
    if (game::HasMask(game::ItemId::DonGeroMask))
      count += 1;
    if (game::HasMask(game::ItemId::KamaroMask))
      count += 1;
    if (game::HasMask(game::ItemId::CaptainHat))
      count += 1;
    if (game::HasMask(game::ItemId::StoneMask))
      count += 1;
    if (game::HasMask(game::ItemId::BremenMask))
      count += 1;
    if (game::HasMask(game::ItemId::BlastMask))
      count += 1;
    if (game::HasMask(game::ItemId::MaskOfScents))
      count += 1;
    if (game::HasMask(game::ItemId::GiantMask))
      count += 1;
    return count;
  }
}  // namespace rnd
