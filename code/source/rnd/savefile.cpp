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
  void SaveFile_Init(u32 fileBaseIndex) {
    game::SaveData &saveData = game::GetCommonData().save;
#ifdef ENABLE_DEBUG
    saveData.equipment.sword_shield.sword = game::SwordType::GildedSword;
    saveData.player.razor_sword_hp = 0x64;
    game::GiveItem(game::ItemId::Ocarina);
    game::GiveItem(game::ItemId::Arrow);
    game::GiveItem(game::ItemId::FireArrow);
    game::GiveItem(game::ItemId::IceArrow);
    game::GiveItem(game::ItemId::LightArrow);
    game::GiveItem(game::ItemId::Bomb);
    game::GiveItem(game::ItemId::Bombchu);
    game::GiveItem(game::ItemId::PictographBox);
    game::GiveItem(game::ItemId::Hookshot);
    saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver50;
    saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag40;
    saveData.inventory.inventory_count_register.wallet_upgrade = 2;
    saveData.inventory.inventory_count_register.stick_upgrades = 2;
    saveData.inventory.inventory_count_register.nut_upgrade = 2;
    saveData.inventory.woodfall_temple_keys = 8;
    saveData.inventory.snowhead_temple_keys = 8;
    saveData.inventory.great_bay_temple_keys = 8;
    saveData.inventory.stone_tower_temple_keys = 8;
    saveData.inventory.woodfall_boss_key = 1;
    saveData.inventory.snowhead_boss_key = 1;
    saveData.inventory.great_bay_boss_key = 1;
    saveData.inventory.stone_tower_boss_key = 1;
    saveData.player.magic_acquired = 1;
    saveData.player.magic_size_type = 2;
    saveData.player.magic = 48;
    saveData.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    saveData.inventory.item_counts[11] = 20; // Bombs
    saveData.inventory.item_counts[12] = 20; // Bombchus
#endif
    //TODO: Decomp event flags. Most likely in the large anonymous structs in the SaveData.
    saveData.has_completed_intro = 1;

    //TODO: Things to set on
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

  /*void SaveFile_SetStartingInventory(void) {
    //give maps and compasses
    if (gSettingsContext.mapsAndCompasses == MAPSANDCOMPASSES_START_WITH) {
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
    }

    //starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
      gSaveContext.items[SLOT_NUT] = ITEM_NUT;
      gSaveContext.items[SLOT_STICK] = ITEM_STICK;
      gSaveContext.upgrades |= 1 << 17;
      gSaveContext.upgrades |= 1 << 20;
      gSaveContext.ammo[SLOT_NUT] = 20;
      gSaveContext.ammo[SLOT_STICK] = 10;
    }

    //main inventory
    if (gSettingsContext.startingStickCapacity > 0) {
      gSaveContext.upgrades |= ((gSettingsContext.startingStickCapacity + 1) << 17);
      gSaveContext.items[SLOT_STICK] = ITEM_STICK;
      gSaveContext.ammo[SLOT_STICK] = (gSettingsContext.startingStickCapacity + 1) * 10;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
      gSaveContext.upgrades |= ((gSettingsContext.startingNutCapacity + 1) << 20);
      gSaveContext.items[SLOT_NUT] = ITEM_NUT;
      gSaveContext.ammo[SLOT_NUT] = (gSettingsContext.startingNutCapacity + 2) * 10;
    }

    if (gSettingsContext.startingBombBag > 0) {
      gSaveContext.upgrades |= (gSettingsContext.startingBombBag << 3);
      gSaveContext.items[SLOT_BOMB] = ITEM_BOMB;
      gSaveContext.ammo[SLOT_BOMB] = (gSettingsContext.startingBombBag + 1) * 10;
    }

    if (gSettingsContext.startingBombchus > 0) {
      gSaveContext.items[SLOT_BOMBCHU] = ITEM_BOMBCHU;
      gSaveContext.ammo[SLOT_BOMBCHU] = 20;
    }

    if (gSettingsContext.startingBow > 0) {
      gSaveContext.upgrades |= (gSettingsContext.startingBow);
      gSaveContext.items[SLOT_BOW] = ITEM_BOW;
      gSaveContext.ammo[SLOT_BOW] = (gSettingsContext.startingBow + 2) * 10;
    }

    if (gSettingsContext.startingFireArrows) {
      gSaveContext.items[SLOT_ARROW_FIRE] = ITEM_ARROW_FIRE;
    }

    if (gSettingsContext.startingIceArrows) {
      gSaveContext.items[SLOT_ARROW_ICE] = ITEM_ARROW_ICE;
    }

    if (gSettingsContext.startingLightArrows) {
      gSaveContext.items[SLOT_ARROW_LIGHT] = ITEM_ARROW_LIGHT;
    }

    if (gSettingsContext.startingDinsFire) {
      gSaveContext.items[SLOT_DINS_FIRE] = ITEM_DINS_FIRE;
    }

    if (gSettingsContext.startingFaroresWind) {
      gSaveContext.items[SLOT_FARORES_WIND] = ITEM_FARORES_WIND;
    }

    if (gSettingsContext.startingNayrusLove) {
      gSaveContext.items[SLOT_NAYRUS_LOVE] = ITEM_NAYRUS_LOVE;
    }

    if (gSettingsContext.startingSlingshot > 0) {
      gSaveContext.upgrades |= (gSettingsContext.startingSlingshot << 14);
      gSaveContext.items[SLOT_SLINGSHOT] = ITEM_SLINGSHOT;
      gSaveContext.ammo[SLOT_SLINGSHOT] = (gSettingsContext.startingSlingshot + 2) * 10;
    }

    if (gSettingsContext.startingBoomerang) {
      gSaveContext.items[SLOT_BOOMERANG] = ITEM_BOOMERANG;
    }

    if (gSettingsContext.startingLensOfTruth) {
      gSaveContext.items[SLOT_LENS] = ITEM_LENS;
    }

    if (gSettingsContext.startingMagicBean) {
      ItemEffect_BeanPack(&gSaveContext, 0, 0);
      gSaveContext.magic_beans_available = 10;
    }

    if (gSettingsContext.startingMegatonHammer) {
      gSaveContext.items[SLOT_HAMMER] = ITEM_HAMMER;
    }

    if (gSettingsContext.startingHookshot > 0) {
      gSaveContext.items[SLOT_HOOKSHOT] = ITEM_HOOKSHOT + (gSettingsContext.startingHookshot - 1);
    }

    if (gSettingsContext.startingIronBoots) {
      gSaveContext.items[SLOT_IRON_BOOTS] = ITEM_BOOTS_IRON;
    }

    if (gSettingsContext.startingHoverBoots) {
      gSaveContext.items[SLOT_HOVER_BOOTS] = ITEM_BOOTS_HOVER;
    }

    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle1, SLOT_BOTTLE_1);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle2, SLOT_BOTTLE_2);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle3, SLOT_BOTTLE_3);
    SaveFile_GiveStartingBottle(gSettingsContext.startingBottle4, SLOT_BOTTLE_4);

    if (gSettingsContext.startingRutoBottle) {
      gSaveContext.items[SLOT_BOTTLE_4] = gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN ? ITEM_BOTTLE : ITEM_LETTER_RUTO;
    }

    if (gSettingsContext.startingOcarina > 0) {
      gSaveContext.items[SLOT_OCARINA] = ITEM_OCARINA_FAIRY + (gSettingsContext.startingOcarina - 1);
    }

    if (gSettingsContext.startingKokiriSword) {
      gSaveContext.childEquips.buttonItems[0] = ITEM_SWORD_KOKIRI;
    }

    if (gSettingsContext.startingBiggoronSword == STARTINGBGS_BIGGORON_SWORD) {
      gSaveContext.bgsFlag = 1;
      gSaveContext.bgsHitsLeft = 1;
    }
    if (gSettingsContext.startingBiggoronSword == STARTINGBGS_GIANTS_KNIFE) {
      gSaveContext.bgsFlag = 0;
      gSaveContext.bgsHitsLeft = GK_SetDurability();
    }

    if (gSettingsContext.startingMagicMeter == 1) {
      ItemEffect_GiveMagic(&gSaveContext, 0, 0);
    } else if (gSettingsContext.startingMagicMeter == 2) {
      ItemEffect_GiveDoubleMagic(&gSaveContext, 0, 0);
    }

    if (gSettingsContext.startingDoubleDefense) {
      ItemEffect_GiveDefense(&gSaveContext, 0, 0);
    }

    gSaveContext.healthCapacity = gSettingsContext.startingHealth << 4;
    gSaveContext.health = gSettingsContext.startingHealth << 4;

    gSaveContext.questItems |= gSettingsContext.startingQuestItems;
    gSaveContext.questItems |= gSettingsContext.startingDungeonReward;
    gSaveContext.equipment |= gSettingsContext.startingEquipment;
    gSaveContext.upgrades |= gSettingsContext.startingUpgrades;

    //max rupees
    if (gSettingsContext.startingMaxRupees) {
      u8 wallet = (gSaveContext.upgrades >> 12) & 0x3;
      if (wallet == 0) {
        gSaveContext.rupees = 99;
      } else if (wallet == 1) {
        gSaveContext.rupees = 200;
      } else if (wallet == 2) {
        gSaveContext.rupees = 500;
      } else {
        gSaveContext.rupees = 999;
      }
    }

    //set token count
    gSaveContext.gsTokens = gSettingsContext.startingTokens;

    //Set Epona as freed if Skip Epona Race is enabled and Epona's Song is in the starting inventory
    if (gSettingsContext.skipEponaRace == SKIP && (gSaveContext.questItems >> 13) & 0x1) {
      EventSet(0x18);
    }
  }
*/
  //Resolve the item ID for the starting bottle
  static void SaveFile_GiveStartingBottle(StartingBottleSetting startingBottle, u8 bottleSlot) {
    game::SaveData &saveData = game::GetCommonData().save;
    if (startingBottle > StartingBottleSetting::STARTINGBOTTLE_NONE) {
      saveData.inventory.bottles[bottleSlot] = (game::ItemId)startingBottle;
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
