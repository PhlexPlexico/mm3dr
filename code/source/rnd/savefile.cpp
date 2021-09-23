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
#endif
  }
}
