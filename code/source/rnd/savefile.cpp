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
    saveData.equipment.sword_sheild.sword = game::SwordType::GildedSword;
    saveData.player.razor_sword_hp = 0x64;
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
    saveData.inventory.items[0] = game::ItemId::Ocarina;
    saveData.inventory.items[1] = game::ItemId::Arrow;
    saveData.inventory.items[2] = game::ItemId::FireArrow;
    saveData.inventory.items[3] = game::ItemId::IceArrow;
    saveData.inventory.items[4] = game::ItemId::LightArrow;
    saveData.inventory.items[5] = game::ItemId::Bomb;
    saveData.inventory.items[6] = game::ItemId::Bombchu;
    saveData.inventory.items[11] = game::ItemId::PictographBox;
    saveData.inventory.items[13] = game::ItemId::Hookshot;
    saveData.inventory.items[15] = game::ItemId::Hookshot;
    saveData.player.magic_acquired = 1;
    saveData.player.magic_size_type = 2;
    saveData.player.magic = 48;
    cdata.save.inventory.item_counts[11] = 20; // Bombs
    cdata.save.inventory.item_counts[12] = 20; // Bombs
#endif
    //TODO: Decomp event flags. Most likely in the large anonymous structs in the SaveData.
    saveData.has_completed_intro = 1;
  }
}
