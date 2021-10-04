#include "rnd/item_table.h"
#include "rnd/item_effect.h"
#include "rnd/item_override.h"
#include "rnd/item_upgrade.h"
#include "rnd/rHeap.h"
#include <stddef.h>

#include "z3D/z3Dvec.h"

extern "C" {
#include <3ds/svc.h>
}

namespace rnd {

#define ITEM_ROW(                                                                                     \
    baseItemId_, chestType_, itemId_, textId_, objectId_, objectModelIdx_, cmabIndex_,                \
    objectModelIdx2_, cmabIndex2_, special_, graphicId_, upgrade_, effect_, effectArg1_, effectArg2_) \
  { .baseItemId = baseItemId_, .chestType = chestType_, .itemId = itemId_, .textId = textId_,         \
    .objectId = objectId_, .objectModelIdx = objectModelIdx_, .cmabIndex = cmabIndex_,                \
    .objectModelIdx2 = objectModelIdx2_, .cmabIndex2 = cmabIndex2_, .special = special_,              \
    .graphicId = graphicId_, .upgrade = upgrade_, .effect = effect_, .effectArg1 = effectArg1_,       \
    .effectArg2 = effectArg2_ }

  // TODO: Convert to C++
  ItemRow rItemTable[] = {
      [0x00] = ITEM_ROW((u32)GetItemID::GI_NONE, ChestType::WOODEN_SMALL, 0xFF, 0x00C4, 0x0000, 0x00, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // None Item - So we don't have to do GetItemId-1 everywhere.

      [0x01] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FiveBombs, 0x0014, 0x00A5, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_BombsToRupee, ItemEffect_None, (s16)-1, (s16)-1), // Bombs (5)

      [0x02] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FiveNuts, 0x0029, 0x0094, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Nuts (5)

      [0x03] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::TenBombchus, 0x0014, 0x00B0, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bombchus (10)

      [0x04] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Arrow, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_PlaceMagicArrowsInInventory, (s16)0, (s16)-1), // Hero's Bow

      [0x05] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::DekuStick, 0x0019, 0x009F, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Stick

      [0x06] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::LensOfTruth, 0x0042, 0x00C0, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Lens of Truth

      [0x07] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Hookshot, 0x0022, 0x00BF, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Hookshot

      [0x08] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreatFairySword, 0x003B, 0x001FB, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Great Fairy Sword

      [0x09] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Bottle, 0x005A, 0x009E, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Empty Bottle

      [0x0A] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::RedPotion, 0x005B, 0x00C1, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Red Potion

      [0x0B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreenPotion, 0x005C, 0x00C1, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Green Potion

      [0x0C] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BluePotion, 0x005D, 0x00C1, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Blue Potion

      [0x0D] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Fairy, 0x005E, 0x0272, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Fairy

      [0x0E] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::DekuPrincess, 0x005F, 0x009E, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Deku Princess

      [0x0F] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Milk, 0x0060, 0x00B6, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Milk

      [0x10] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Fish, 0x0062, 0x00C7, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Fish

      [0x11] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Bug, 0x0063, 0x0137, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Bug

      [0x12] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BigPoe, 0x0066, 0x0139, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Big Poe

      [0x13] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::Water, 0x0067, 0x009E, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Water

      [0x14] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::HotSpringWater, 0x0068, 0x009E, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Hot Spring Water

      [0x15] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::X82, 0x0014, 0x00FF, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_IceTrap, (s16)-1, (s16)-1), // Ice Trap 0x13

      [0x16] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::ZoraEgg, 0x0069, 0x01AE, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Zora Egg

      [0x17] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GoldDust, 0x006A, 0x01E9, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Gold Dust

      [0x18] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MagicalMushroom, 0x006B, 0x021D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Magic Mushrooms

      [0x19] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::SeaHorse, 0x006E, 0x01F0, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Sea Horse

      [0x1A] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::ChateauRomani, 0x006F, 0x0227, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Chateau Romani

      // XXX: Trade Item, may have to change values? Seems rather individual and leads to fishing pass.
      [0x1B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MysteryMilk, 0x00CE, 0x00B6, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bottle With Mystery Milk

      // TODO: Trade quest items
      [0x1C] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MoonTear, 0x0096, 0x01B1, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Moon's Tear

      [0x1D] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::LandTitleDeed, 0x0097, 0x01B2, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Land Title Deed

      [0x1E] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::SwampTitleDeed, 0x0098, 0x01B2, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Swamp Title Deed

      [0x1F] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MountainTitleDeed, 0x0099, 0x01B2, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Mountain Title Deed

      [0x20] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::OceanTitleDeed, 0x009A, 0x01B2, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Ocean Title Deed

      [0x21] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::RoomKey, 0x00A0, 0x020F, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Room Key

      [0x22] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::LetterToMama, 0x00A1, 0x0245, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Letter To Mama

      [0x23] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::LetterToKafei, 0x00AA, 0x0210, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Letter To Kafei

      [0x24] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::LetterToKafei, 0x00AB, 0x0215, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Pendant Of Memories
      // END TRADE QUEST ITEMS

      [0x25] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::MapUnused, 0x00B4, 0x024D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Map of Clocktown

      [0x26] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::MapUnused, 0x00B5, 0x024D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Map of Woodfall

      [0x27] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::MapUnused, 0x00B6, 0x024D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Map of Snowhead

      [0x28] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::MapUnused, 0x00B7, 0x024D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Map of Great Bay

      [0x29] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::MapUnused, 0x00B8, 0x024D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Map of Stone Tower

      [0x2A] = ITEM_ROW((u32)GetItemID::GI_RUPEE_BLUE, ChestType::WOODEN_SMALL, (u8)game::ItemId::FishingPass, 0x00CF, 0x029B, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Fishing Pass

      // Masks
      [0x2B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::DekuMask, 0x0078, 0x01BD, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Deku Mask

      [0x2C] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GoronMask, 0x0079, 0x0119, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Goron Mask

      [0x2D] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::ZoraMask, 0x007A, 0x011A, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Goron Mask

      [0x2E] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::FierceDeityMask, 0x007B, 0x0242, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Fierce Deity Mask

      [0x2F] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::CaptainHat, 0x007C, 0x0102, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Captain Hat

      [0x30] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GiantMask, 0x007D, 0x0226, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Giant Mask

      [0x31] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::AllNightMask, 0x007E, 0x0265, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // All Night Mask

      [0x32] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BunnyHood, 0x007F, 0x0103, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bunny Hood

      [0x33] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::KeatonMask, 0x0080, 0x0100, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Keaton Mask

      [0x34] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GaroMask, 0x0081, 0x0209, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Garo Mask

      [0x35] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::RomaniMask, 0x0082, 0x021F, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Romani Mask

      [0x36] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::CircusLeaderMask, 0x0083, 0x0259, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Circus Leader Mask

      [0x37] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::PostmanHat, 0x0084, 0x0225, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Postman Hat

      [0x38] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::CoupleMask, 0x0085, 0x0282, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Couple's Mask

      [0x39] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GreatFairyMask, 0x0086, 0x020A, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Great Fairy's Mask

      [0x3A] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GibdoMask, 0x0087, 0x020B, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Gibdo's Mask

      [0x3B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::DonGeroMask, 0x0088, 0x0266, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Don Gero's Mask

      [0x3C] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::KamaroMask, 0x0089, 0x027D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Kamaro's Mask

      [0x3D] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MaskOfTruth, 0x008A, 0x0104, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Mask of Truth

      [0x3E] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::StoneMask, 0x008B, 0x0254, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Stone Mask

      [0x3F] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BremenMask, 0x008C, 0x025A, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Bremen Mask

      [0x40] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::BlastMask, 0x008D, 0x026D, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Blast Mask

      [0x41] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MaskOfScents, 0x008E, 0x027E, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Mask Of Scents

      [0x42] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::KafeiMask, 0x008F, 0x0258, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Kafei Mask

      [0x43] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MaskOfScents, 0x008E, 0x027E, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Mask Of Scents
      // End Masks

      // The following bottle items either give one bottle if you do not have one, or refills any bottle if you do have an empty one.
      // Essentially acts as if you caught something in a bottle.
      [0x44] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::ChateauRomaniFill, 0x0091, 0x0227, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Cheateu Refill

      [0x45] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MilkFill, 0x0092, 0x00B6, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Milk Refill

      [0x46] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GoldDustFill, 0x0093, 0x001E8, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Gold Dust Refill

      [0x47] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::SeahorseFill, 0x0095, 0x001F0, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Seahorse Refill

      [0x48] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::KokiriSword, 0x0037, 0x00148, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_Sword, ItemEffect_None, (s16)-1, (s16)-1), // Kokiri Sword

      [0x49] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::RazorSword, 0x0038, 0x00148, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_Sword, ItemEffect_None, (s16)-1, (s16)-1), // Razor Sword

      [0x4A] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::GildedSword, 0x0039, 0x001FA, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_Sword, ItemEffect_None, (s16)-1, (s16)-1), // Gilded Sword

      [0x4B] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::HeroShield, 0x0032, 0x000B3, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Hero Sheild

      [0x4C] = ITEM_ROW((u32)GetItemID::GI_NUTS_30, ChestType::WOODEN_BIG, (u8)game::ItemId::MirrorShield, 0x0033, 0x000C3, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_None, ItemEffect_None, (s16)-1, (s16)-1), // Hero Sheild

      // Progressive Items
      [0x4D] = ITEM_ROW(0xFF, ChestType::WOODEN_BIG, 0xFF, 0xFF, 0x00098, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_BombBag, ItemEffect_None, (s16)-1, (s16)-1), // Progressive Bomb Bag

      [0x4E] = ITEM_ROW(0xFF, ChestType::WOODEN_BIG, 0xFF, 0xFF, 0x00097, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_Quiver, ItemEffect_None, (s16)-1, (s16)-1), // Progressive Quiver

      [0x4F] = ITEM_ROW(0xFF, ChestType::WOODEN_BIG, 0xFF, 0xFF, 0x000A8, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_Wallet, ItemEffect_None, (s16)-1, (s16)-1), // Progressive Wallet

      [0x50] = ITEM_ROW(0xFF, ChestType::WOODEN_BIG, 0xFF, 0xFF, 0x000A4, (s8)0xFF, (s8)0xFF,
                        (s8)0xFF, (s8)0xFF, (s8)0xFF, 0xFF, (rnd::upgradeFunc)ItemUpgrade_Magic, ItemEffect_None, (s16)-1, (s16)-1), // Progressive Magic
  };

  ItemRow *ItemTable_GetItemRow(u16 itemId) {
    if (itemId >= ARR_SIZE(rItemTable)) {
      return NULL;
    }
    ItemRow *itemRow = &rItemTable[18];
    if (itemRow->baseItemId == 0) {
      return NULL;
    }
    return itemRow;
  }

  ItemRow *ItemTable_GetItemRowFromIndex(u8 rowIndex) {
    return &rItemTable[rowIndex];
  }

  void ItemTable_SetBombchusChestType(u8 type) {
    //rItemTable[0x6B].chestType = type;
  }

  u16 ItemTable_ResolveUpgrades(u16 itemId) {
    game::SaveData &gSaveContext = game::GetCommonData().save;
    if (gSaveContext.has_completed_intro) {
      for (;;) {
        ItemRow *itemRow = ItemTable_GetItemRow(itemId);
        u16 newItemId = (u16)itemRow->upgrade(&gSaveContext, (GetItemID)itemId);
        if (newItemId == itemId) {
          return itemId;
        }
        itemId = newItemId;
      }
    }
    // Should not reach.
    return 0;
  }

  void ItemTable_CallEffect(ItemRow *itemRow) {
    game::CommonData &commonData = game::GetCommonData();
    itemRow->effect(&commonData, itemRow->effectArg1, itemRow->effectArg2);
  }

} // namespace rnd
