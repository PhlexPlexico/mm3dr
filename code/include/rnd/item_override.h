#ifndef _RND_ITEM_OVERRIDE_H
#define _RND_ITEM_OVERRIDE_H

#include "common/advanced_context.h"
#include "common/utils.h"
#include "game/actors/great_fairy.h"
#include "game/common_data.h"
#include "game/context.h"
#include "game/items.h"
#include "z3d/z3DVec.h"

namespace rnd {

  enum class GetItemID : u32 {
    /* 0x00 */ GI_NONE,
    /* 0x01 */ GI_RUPEE_GREEN,
    /* 0x02 */ GI_RUPEE_BLUE,
    /* 0x03 */ GI_RUPEE_10,
    /* 0x04 */ GI_RUPEE_RED,
    /* 0x05 */ GI_RUPEE_PURPLE,
    /* 0x06 */ GI_RUPEE_SILVER,
    /* 0x07 */ GI_RUPEE_GOLD,
    /* 0x08 */ GI_ADULT_WALLET,
    /* 0x09 */ GI_GIANT_WALLET,
    /* 0x0A */ GI_RECOVERY_HEART_SINGLE,      // No actor, just sound and recovery.
    /* 0x0B */ GI_RECOVERY_HEART_SINGLE_TWO,  // No actor, just sound and recovery.
    /* 0x0C */ GI_HEART_PIECE,
    /* 0x0D */ GI_HEART_CONTAINER,
    /* 0x0E */ GI_MAGIC_POT_SMALL,              // Item above head, no animation like 0x01.
    /* 0x0F */ GI_MAGIC_POT_LARGE,              // Item above head, no animation like 0x01.
    /* 0x10 */ GI_RECOVERY_HEART_SINGLE_THREE,  // No actor, just sound and recovery.
    /* 0x11 */                                  // GI_ERROR_NOTHING_11, // Item above head, no animation like 0x01.
    /* 0x12 */ GI_RECOVERY_HEART_SINGLE_FOUR = 0x12,  // No actor, just sound and recovery.
    /* 0x13 */ GI_RECOVERY_HEART_SINGLE_FIVE,         // No actor, just sound and recovery.,
    /* 0x14 */ GI_BOMBS_1,                            // Item above head, no animation like 0x01. Bomb bag required.
    /* 0x15 */ GI_BOMBS_5,                            // Item above head, no animation like 0x01.
    /* 0x16 */ GI_BOMBS_10,
    /* 0x17 */ GI_BOMBS_20,
    /* 0x18 */ GI_BOMBS_30,
    /* 0x19 */ GI_STICKS_1,
    /* 0x1A */ GI_BOMBCHUS_10,
    /* 0x1B */ GI_BOMB_BAG_20,
    /* 0x1C */ GI_BOMB_BAG_30,
    /* 0x1D */ GI_BOMB_BAG_40,
    /* 0x1E */ GI_ARROWS_SMALL,
    /* 0x1F */ GI_ARROWS_MEDIUM,
    /* 0x20 */ GI_ARROWS_LARGE,
    /* 0x21 */ GI_ARROWS_LARGEST,
    /* 0x22 */ GI_HEROS_BOW,
    /* 0x23 */ GI_LARGE_QUIVER,
    /* 0x24 */ GI_LARGEST_QUIVER,
    /* 0x25 */ GI_FIRE_ARROW,
    /* 0x26 */ GI_ICE_ARROW,
    /* 0x27 */ GI_LIGHT_ARROW,
    /* 0x28 */ GI_NUTS_1,
    /* 0x29 */ GI_NUTS_5,
    /* 0x2A */ GI_NUTS_10,
    /* 0x2B */ GI_NUTS_30,  // ***ERROR TEXT
    /* 0x2C */              // GI_ERROR_MAX_NUT, // ***ERROR TEXT MaxNut
    /* 0x2D */              // GI_UNK_2D, // Softlock
    /* 0x2E */ GI_BOMBCHU_20 = 0x2E,
    /* 0x2F */  // GI_ERROR_MAX_STICK, // ***ERROR TEXT MaxStick
    /* 0x30 */  // GI_ERROR_MAX_STICK_TWO, // ***ERROR TEXT MaxStick
    /* 0x31 */  // GI_ERROR_MAX_STICK_THREE, // ***ERROR TEXT MaxStick
    /* 0x32 */ GI_SHIELD_HERO = 0x32,
    /* 0x33 */ GI_SHIELD_MIRROR,
    /* 0x34 */ GI_POWDER_KEG,
    /* 0x35 */ GI_MAGIC_BEAN,
    /* 0x36 */ GI_BOMBCHUS_1,
    /* 0x37 */ GI_KOKIRI_SWORD,  // ***ERROR TEXT Kokiri Sword - No text to begin with. Possible
                                 // edit/patch?
    /* 0x38 */ GI_RAZOR_SWORD,
    /* 0x39 */ GI_GILDED_SWORD,
    /* 0x3A */ GI_BOMBCHUS_5,
    /* 0x3B */ GI_GREAT_FAIRY_SWORD,
    /* 0x3C */ GI_KEY_SMALL,
    /* 0x3D */ GI_KEY_BOSS,
    /* 0x3E */ GI_MAP,               // Item pickup noise. Perhaps dungeon specific?
    /* 0x3F */ GI_COMPASS,           // Item pickup noise. Perhaps dungeon specific?
    /* 0x40 */ GI_ERROR_NOTHING_40,  // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                     // Ocarina in Inventory
                                     // XXX: ICE TRAP
    /* 0x41 */ GI_HOOKSHOT,          // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in
                                     // Inventory
    /* 0x42 */ GI_LENS_OF_TRUTH = 0x42,
    /* 0x43 */ GI_PICTOGRAPH_BOX = 0x43,
    /* 0x44 */  // GI_ERROR_PICTOGRAPH_BOX, // ***ERROR TEXT Get Item Nothing in hand - Gives
                // pictograph box
    /* 0x45 */  // GI_ERROR_NOTHING_45, // Recovery Heart, no actor above head.
    /* 0x46 */  // GI_ERROR_NOTHING_46, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x47 */  // GI_ERROR_NOTHING_47, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x48 */  // GI_ERROR_NOTHING_48, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x49 */  // GI_ERROR_NOTHING_49, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x4A */  // GI_ERROR_NOTHING_4A, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x4B */  // GI_ERROR_NOTHING_4B, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x4C */ GI_OCARINA_OF_TIME = 0x4C,
    /* 0x4D */  // GI_ERROR_NOTHING_4D, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x4E */  // GI_ERROR_NOTHING_4E, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x4F */  // GI_ERROR_NOTHING_4F, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x50 */ GI_BOMBERS_NOTEBOOK = 0x50,
    /* 0x51 */  // GI_ERROR_YELLOW_RUPPEE, // ***ERROR TEXT Get Item Nothing in hand at first - then
                // subsequently yellow rupee. No rupee increment.
    /* 0x52 */ GI_GOLD_SKULLTULA_SPIRIT = 0x52,  // Pickup model is whacky since we usually don't have one.
    /* 0x53 */  // GI_ERROR_NOTHING_53, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x54 */  // GI_ERROR_NOTHING_54, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x55 */ GI_ODOLWAS_REMAINS = 0x55,  // Also softlocks!
    /* 0x56 */ GI_GOHTS_REMAINS,           // Also softlocks!
    /* 0x57 */ GI_GYORGS_REMAINS,          // Also softlocks!
    /* 0x58 */ GI_TWINMOLDS_REMAINS,       // Also softlocks!
    /* 0x59 */ GI_BOTTLE_POTION_RED,
    /* 0x5A */ GI_BOTTLE_EMPTY,
    /* 0x5B */ GI_POTION_RED,           // If all bottles in item screen are full, it gives recovery hearts.
    /* 0x5C */ GI_POTION_GREEN,         // Does not give new bottles.
    /* 0x5D */ GI_POTION_BLUE,          // Does not give new bottles.
    /* 0x5E */ GI_FAIRY,                // Does not give new bottles.
    /* 0x5F */ GI_DEKU_PRINCESS_FAIRY,  // Shows Deku Princess Text but gives fairy
    /* 0x60 */ GI_BOTTLE_MILK = 0x60,
    /* 0x61 */ GI_BOTTLE_MILK_HALF,  // ***ERROR TEXT Get Item Milk In Hand - Keeps Giving Bottles
    /* 0x62 */ GI_BOTTLE_FISH,
    /* 0x63 */ GI_BOTTLE_BUG,
    /* 0x64 */ GI_BOTTLE_BLUE_FIRE,  // ***ERROR TEXT - Not implemented in game.
    /* 0x65 */ GI_BOTTLE_POE_TEXT,   // Gives poe text but empty bottle.
    /* 0x66 */ GI_BOTTLE_BIG_POE,
    /* 0x67 */ GI_BOTTLE_SPRING_WATER,      // No actor on GetItem.
    /* 0x68 */ GI_BOTTLE_HOT_SPRING_WATER,  // No actor on GetItem. Doesn't activate timer
    /* 0x69 */ GI_BOTTLE_ZORA_EGG,
    /* 0x6A */ GI_BOTTLE_GOLD_DUST,
    /* 0x6B */ GI_BOTTLE_MAGIC_MUSHROOM,
    /* 0x6C */  // GI_ERROR_NOTHING_6C, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x6D */  // GI_BOTTLE_EMPTY_ERROR_TEXT,
    /* 0x6E */ GI_BOTTLE_SEAHORSE = 0x6E,  // Gold Dust Actor lol
    /* 0x6F */ GI_BOTTLE_CHATEAU_ROMANI,
    /* 0x70 */ GI_BOTTLE_MYSTERY_MILK,  // Activates Timer
    /* 0x71 */ GI_BOTTLE_MOLDY_MILK,    // Mystery milk text followed by tatl.
    /* 0x72 */  // GI_ERROR_NOTHING_72, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x73 */  // GI_ERROR_NOTHING_73, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x74 */  // GI_ERROR_NOTHING_74, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x75 */  // GI_ERROR_NOTHING_75, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x76 */  // GI_ERROR_NOTHING_76, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x77 */  // GI_ERROR_NOTHING_77, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
    /* 0x78 */ GI_MASK_DEKU = 0x78,
    /* 0x79 */ GI_MASK_GORON,
    /* 0x7A */ GI_MASK_ZORA,
    /* 0x7B */ GI_MASK_FIERCE_DEITY,
    /* 0x7C */ GI_MASK_CAPTAINS_HAT,
    /* 0x7D */ GI_MASK_GIANTS,
    /* 0x7E */ GI_MASK_ALL_NIGHT,
    /* 0x7F */ GI_MASK_BUNNY_HOOD,
    /* 0x80 */ GI_MASK_KEATON,
    /* 0x81 */ GI_MASK_GARO,
    /* 0x82 */ GI_MASK_ROMANIS,
    /* 0x83 */ GI_MASK_TROUPE_LEADERS,
    /* 0x84 */ GI_MASK_POSTMANS,
    /* 0x85 */ GI_MASK_COUPLES,
    /* 0x86 */ GI_MASK_GREAT_FAIRYS,
    /* 0x87 */ GI_MASK_GIBDO,
    /* 0x88 */ GI_MASK_DON_GEROS,
    /* 0x89 */ GI_MASK_KAMARAOS,
    /* 0x8A */ GI_MASK_OF_TRUTH,
    /* 0x8B */ GI_MASK_STONE,
    /* 0x8C */ GI_MASK_BREMEN,
    /* 0x8D */ GI_MASK_BLAST,
    /* 0x8E */ GI_MASK_OF_SCENTS,
    /* 0x8F */ GI_MASK_KAFEIS,
    /* 0x90 */  // GI_ERROR_NOTHING_90, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory
                // clang-format off
    /* 0x91 */ GI_BOTTLE_CHATEAU_ROMANI_REFILL = 0x91,
                                               // Sets it in a different slot if no bottle present. Second bottle?
                // clang-format on
    /* 0x92 */ GI_BOTTLE_MILK_REFILL,          // Sets it in a different slot if no bottle present. Second
                                               // bottle?
    /* 0x93 */ GI_BOTTLE_GOLD_DUST_REFILL,     // Sets it in a different slot if no bottle present. Second
                                               // bottle?
    /* 0x94 */ GI_BOTTLE_MYSTERY_MILK_REFILL,  // Timer set to 0.
    /* 0x95 */ GI_BOTTLE_SEAHORSE_REFILL,      // Proper sea horse actor!
    /* 0x96 */ GI_MOONS_TEAR,                  // Provides a black screen after collecting in citra.
    /* 0x97 */ GI_TOWN_TITLE_DEED,
    /* 0x98 */ GI_SWAMP_TITLE_DEED,
    /* 0x99 */ GI_MOUNTAIN_TITLE_DEED,
    /* 0x9A */ GI_OCEAN_TITLE_DEED,
    /* 0x9B */ GI_SWORD_GREAT_FAIRY_STOLEN,
    /* 0x9C */ GI_SWORD_KOKIRI_STOLEN,   // Text for when sword gets stolen.
    /* 0x9D */ GI_SWORD_RAZOR_STOLEN,    // Text for when sword gets stolen.
    /* 0x9E */ GI_SWORD_GILDED_STOLEN,   // Text for when sword gets stolen.
    /* 0x9F */ GI_SHIELD_HERO_2_STOLEN,  // Code that treats this as hero's shield is unused, so
                                         // take with a grain of salt
    /* 0xA0 */ GI_ROOM_KEY,              // Softlocks if you go to the room
    /* 0xA1 */ GI_LETTER_TO_MAMA,
    /* 0xA2 */                    // GI_ERROR_NOTHING_A2, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                  // Ocarina in Inventory
    /* 0xA3 */                    // GI_ERROR_NOTHING_A3, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                  // Ocarina in Inventory
    /* 0xA4 */                    // GI_ERROR_NOTHING_A4, // ***ERROR TEXT Get Item Keaton Mask if do not have.
    /* 0xA5 */                    // GI_ERROR_NOTHING_A5, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                  // Ocarina in Inventory
    /* 0xA6 */                    // GI_ERROR_NOTHING_A6, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                  // Ocarina in Inventory
    /* 0xA7 */                    // GI_ERROR_NOTHING_A7, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                  // Ocarina in Inventory
    /* 0xA8 */                    // GI_ERROR_NOTHING_A8, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                                  // Ocarina in Inventory,
    /* 0xA9 */ GI_BOTTLE = 0xA9,  // Bottle purchase back text.
    /* 0xAA */ GI_LETTER_TO_KAFEI,
    /* 0xAB */ GI_PENDANT_OF_MEMORIES,
    /* 0xAC */  // GI_ERROR_NOTHING_AC, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xAD */  // GI_ERROR_NOTHING_AD, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xAE */  // GI_ERROR_NOTHING_AE, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xAF */  // GI_ERROR_NOTHING_AF, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xB0 */  // GI_ERROR_NOTHING_B0, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xB1 */  // GI_ERROR_NOTHING_B1, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xB2 */  // GI_ERROR_NOTHING_B2, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with
                // Ocarina in Inventory,
    /* 0xB3 */  // GI_ERROR_SUN_MASK_B3, // ***ERROR TEXT Get Item Sun's Mask in hand - Takes away
                // ocarina if you have it.
    /* 0xB4 */ GI_MAP_OF_CLOCK_TOWN = 0xB4,
    /* 0xB5 */ GI_MAP_OF_WOODFALL,
    /* 0xB6 */ GI_MAP_OF_SNOWHEAD,
    /* 0xB7 */ GI_MAP_OF_ROMANI_RANCH,
    /* 0xB8 */ GI_MAP_OF_GREAT_BAY,
    /* 0xB9 */ GI_MAP_OF_STONE_TOWER,
    /* 0xBA */ GI_FISHING_HOLE_PASS,
  };

  enum class DrawGraphicItemID : s32 {
    /* 0x0000 */ DI_NONE,
    /* 0x0001 */ DI_EMPTY_BOTTLE,
    /* 0x0002 */ DI_SMALL_KEY,
    /* 0x0003 */ DI_KAMARO_MASK,
    /* 0x0004 */ DI_COUPLES_MASK,
    /* 0x0005 */ DI_BROKEN_RUPEE_ONE,
    /* 0x0006 */ DI_BROKEN_RUPEE_TWO,
    /* 0x0007 */ DI_BROKEN_RUPEE_THREE,
    /* 0x0008 */ DI_BROKEN_RUPEE_FOUR,
    /* 0x0009 */ DI_RECOVERY_HEART,
    /* 0x000A */ DI_BOSS_KEY,
    /* 0x000B */ DI_COMPASS,
    /* 0x000C */ DI_BOMBERS_NOTEBOOK,
    /* 0x000D */ DI_STONE_MASK,
    /* 0x000E */ DI_KAFEI_MASK,
    /* 0x000F */ DI_CIRCUS_LEADER_MASK,
    /* 0x0010 */ DI_BREMEN_MASK,
    /* 0x0011 */ DI_ALL_NIGHT_MASK,
    /* 0x0012 */ DI_DEKU_NUT,
    /* 0x0013 */ DI_HEART_CONTAINER,
    /* 0x0014 */ DI_HEART_PIECE,
    /* 0x0015 */ DI_QUIVER,
    /* 0x0016 */ DI_LARGE_QUIVER,
    /* 0x0017 */ DI_BIGGEST_QUIVER,
    /* 0x0018 */ DI_BOMB_BAG,
    /* 0x0019 */ DI_BIG_BOMB_BAG,
    /* 0x001A */ DI_BIGGEST_BOMB_BAG,
    /* 0x001B */ DI_DEKU_STICK,
    /* 0x001C */ DI_TOWN_MAP,
    /* 0x001D */ DI_SMALL_MAGIC_JAR,
    /* 0x001E */ DI_BIG_MAGIC_JAR,
    /* 0x001F */ DI_BOMB,
    /* 0x0020 */ DI_BROKEN_RUPEE_FIVE,
    /* 0x0021 */ DI_ADULT_WALLET,
    /* 0x0022 */ DI_GIANT_WALLET,
    /* 0x0023 */ DI_DON_GERO_MASK,
    /* 0x0024 */ DI_SINGLE_ARROW,
    /* 0x0025 */ DI_BUNDLE_ARROW_SMALL,
    /* 0x0026 */ DI_BUNDLE_ARROW_LARGE,
    /* 0x0027 */ DI_BOMBCHU,
    /* 0x0028 */ DI_HERO_SHIELD,
    /* 0x0029 */ DI_HOOKSHOT,
    /* 0x002A */ DI_HOOKSHOT_TWO,
    /* 0x002B */ DI_OCARINA_OF_TIME,
    /* 0x002C */ DI_MILK_FULL,
    /* 0x002D */ DI_KEATON_MASK,
    /* 0x002E */ DI_DUNGEON_MAP_MAYBE,
    /* 0x002F */ DI_HERO_BOW,
    /* 0x0030 */ DI_LENS_OF_TRUTH,
    /* 0x0031 */ DI_GREEN_POTION,
    /* 0x0032 */ DI_RED_POTION,
    /* 0x0033 */ DI_BLUE_POTION,
    /* 0x0034 */ DI_MIRROR_SHIELD,
    /* 0x0035 */ DI_MAGIC_BEAN,
    /* 0x0036 */ DI_BOTTLE_FISH,
    /* 0x0037 */ DI_MAMAS_LETTER,
    /* 0x0038 */ DI_BROKEN_RUPEE_SIX,
    /* 0x0039 */ DI_BROKEN_RUPEE_SEVEN,
    /* 0x003A */ DI_SUN_MASK,
    /* 0x003B */ DI_BLAST_MASK,
    /* 0x003C */ DI_BOTTLE_FAIRY,
    /* 0x003D */ DI_MASK_OF_SCENTS,
    /* 0x003E */ DI_CAPTAINS_HAT,
    /* 0x003F */ DI_BUNNY_HOOD,
    /* 0x0040 */ DI_MASK_OF_TRUTH,
    /* 0x0041 */ DI_SWAMP_TITLE_DEED,
    /* 0x0042 */ DI_MOUNTAIN_TITLE_DEED,
    /* 0x0043 */ DI_GOLD_RUPEE,
    /* 0x0044 */ DI_OCEAN_TITLE_DEED,
    /* 0x0045 */ DI_GORON_MASK,
    /* 0x0046 */ DI_ZORA_MASK,
    /* 0x0047 */ DI_BROKEN_RUPEE_EIGHT,
    /* 0x0048 */ DI_FIRE_ARROW,
    /* 0x0049 */ DI_ICE_ARROW,
    /* 0x004A */ DI_LIGHT_ARROW,
    /* 0x004B */ DI_GOLD_SKULLTULA_BROKEN,
    /* 0x004C */ DI_BOTTLE_BUG,
    /* 0x004D */ DI_BROKEN_RUPEE_NINE,
    /* 0x004E */ DI_BOTTLE_POE,
    /* 0x004F */ DI_BOTTLE_BIG_POE_PURPLE,
    /* 0x0050 */ DI_GREEN_RUPEE,
    /* 0x0051 */ DI_BLUE_RUPEE,
    /* 0x0052 */ DI_RED_RUPEE,
    /* 0x0053 */ DI_BOTTLE_BIG_POE,
    /* 0x0054 */ DI_PURPLE_RUPEE,
    /* 0x0055 */ DI_SILVER_RUPEE,
    /* 0x0056 */ DI_KOKIRI_SWORD,
    /* 0x0057 */ DI_GOLD_SKULLTULA,
    /* 0x0058 */ DI_BOTTLE_RED_POTION,
    /* 0x0059 */ DI_BOTTLE_ZORA_EGG,
    /* 0x005A */ DI_MOONS_TEAR,
    /* 0x005B */ DI_TOWN_TITLE_DEED,
    /* 0x005C */ DI_DEKU_MASK,
    /* 0x005D */ DI_ODOLWAS_REMAINS,
    /* 0x005E */ DI_POWDER_KEG,
    /* 0x005F */ DI_GOLD_DUST,
    /* 0x0060 */ DI_BOTTLE_GOLD_DUST,
    /* 0x0061 */ DI_BROKEN_RUPEE_TEN,
    /* 0x0062 */ DI_BROKEN_RUPEE_ELEVEN,
    /* 0x0063 */ DI_BOTTLE_SEAHORSE,
    /* 0x0064 */ DI_GOHTS_REMAINS,
    /* 0x0065 */ DI_GYORGS_REMAINS,
    /* 0x0066 */ DI_TWINMOLDS_REMAINS,
    /* 0x0067 */ DI_RAZOR_SWORD,
    /* 0x0068 */ DI_GILDED_SWORD,
    /* 0x0069 */ DI_GREAT_FAIRY_SWORD,
    /* 0x006A */ DI_GARO_MASK,
    /* 0x006B */ DI_GREAT_FAIRY_MASK,
    /* 0x006C */ DI_GIBDO_MASK,
    /* 0x006D */ DI_ROOM_KEY,
    /* 0x006E */ DI_LETTER_TO_KAFEI,
    /* 0x006F */ DI_PENDANT_OF_MEMORIES,
    /* 0x0070 */ DI_BOTTLE_MAGIC_MUSHROOM,
    /* 0x0071 */ DI_ROMANIS_MASK,
    /* 0x0072 */ DI_POSTMANS_HAT,
    /* 0x0073 */ DI_GIANTS_MASK,
    /* 0x0074 */ DI_BOTTLE_CHATEAU_ROMANI,
    /* 0x0075 */ DI_PICTOGRAPH_BOX,
    /* 0x0076 */ DI_FIERCE_DEITY_MASK,
    /* 0x0077 */ DI_NONE_TWO,
    /* 0x0078 */ DI_BOTTLE_WATER_HALF,
    /* 0x0079 */ DI_BOTTLE_HOT_SPRING_WATER_HALF,
    /* 0x007A */ DI_BOTTLE_DEKU_PRINCESS,
    /* 0x007B */ DI_OCARINA_DEKU_PIPES,
    /* 0x007C */ DI_OCARINA_GORON_DRUMS,
    /* 0x007D */ DI_OCARINA_ZORA_GUITAR,
    /* 0x007E */ DI_BOTTLE_GREEN_POTION,
    /* 0x007F */ DI_BOTTLE_BLUE_POTION,
    /* 0x0080 */ DI_BOTTLE_MILK_HALF,
    /* 0x0081 */ DI_PENDANT_OF_MEMORIES_TWO,
    /* 0x0082 */ DI_BOTTLE_BIG_POE_PURPLE_TWO,
    /* 0x0083 */ DI_BOTTLE_MYSTERY_MILK,
    /* 0x0084 */ DI_BOTTLE_MILK,
    /* 0x0085 */ DI_STRAY_FAIRY_CLOCK_TOWN,
    /* 0x0086 */ DI_STRAY_FAIRY_WOODFALL,
    /* 0x0087 */ DI_STRAY_FAIRY_SNOWHEAD,
    /* 0x0088 */ DI_STRAY_FAIRY_GREAT_BAY,
    /* 0x0089 */ DI_STRAY_FAIRY_STONE_TOWER,
    /* 0x008A */ DI_FISHING_PASS,
    /* 0x008B */ DI_HERO_BOW_AND_ARROW,
    /* 0x008C */ DI_HERO_BOW_AND_FIRE_ARROW,
    /* 0x008D */ DI_HERO_BOW_AND_ICE_ARROW,
    /* 0x008E */ DI_HERO_BOW_AND_LIGHT_ARROW,
    /* 0x008F */ DI_NONE_THREE,
    /* 0x0090 */ DI_NONE_FOUR,
  };

  enum class ItemOverride_Type : u8 {
    OVR_BASE_ITEM = 0,
    OVR_CHEST = 1,
    OVR_COLLECTABLE = 2,
    OVR_SKULL = 3,
    OVR_GROTTO_SCRUB = 4,
    OVR_DELAYED = 5,
    OVR_TEMPLE = 6,
  };

  typedef union ItemOverride_Key {
    u32 all;
    struct {
      char pad_;
      u8 scene;
      ItemOverride_Type type;
      u8 flag;
    };
  } ItemOverride_Key;

  typedef union ItemOverride_Value {
    u32 all;
    struct {
      u16 getItemId;
      u8 player;
      u8 looksLikeItemId;
    };
  } ItemOverride_Value;

  struct ItemOverride {
    ItemOverride_Key key;
    ItemOverride_Value value;
  };

  ItemOverride ItemOverride_LookupByKey(ItemOverride_Key);
  void ItemOverride_PushDelayedOverride(u8);
  s32 ItemOverride_IsAPendingOverride(void);
  ItemOverride ItemOverride_Lookup(game::act::Actor*, u16, s16);
  void ItemOverride_PushDungeonReward(u8);
  void ItemOverride_CheckStartingItem();
  void ItemOverride_Init();
  void ItemOverride_Update();
  void ItemOverride_RevealMapBasedOnId(u8);
  void SetExtData(void);
  extern "C" bool ItemOverride_CheckAromaGivenItem();
  extern "C" bool ItemOverride_CheckMikauGivenItem();
  extern "C" bool ItemOverride_CheckDarmaniGivenItem();
  extern "C" void ItemOverride_GetItemTextAndItemID(game::act::Player*);
  extern "C" void ItemOverride_GetItem(game::GlobalContext*, game::act::Actor*, game::act::Player*, s16);
  extern "C" void ItemOverride_GetFairyRewardItem(game::GlobalContext*, game::act::GreatFairy*, s16);
  extern "C" void ItemOverride_GetSoHItem(game::GlobalContext*, game::act::Actor*, s16);
  extern "C" int ItemOverride_CheckInventoryItemOverride(game::ItemId);
  extern "C" void ItemOverride_SwapSoHGetItemText(game::GlobalContext*, u16, game::act::Actor*);
  extern "C" bool ItemOverride_CheckTingleMaps(u16, game::GlobalContext*);
  extern "C" u32 ItemOverride_GetGaboraExtData();
  extern "C" u32 ItemOverride_GetOshExtData();
  extern "C" u32 rActiveItemGraphicId;
  extern "C" ItemOverride rItemOverrides[640];
  extern "C" u16 rStoredTextId;
}  // namespace rnd

#endif
