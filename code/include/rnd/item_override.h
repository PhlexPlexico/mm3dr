#ifndef _GAME_ITEM_OVERRIDE_H
#define _GAME_ITEM_OVERRIDE_H

#include "common/advanced_context.h"
#include "common/utils.h"
#include "game/common_data.h"
#include "z3d/z3Dvec.h"

namespace rnd {

  // Shotouts to MM Decomp for this list so far.
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
    /* 0x0A */ GI_RECOVERY_HEART_SINGLE, // No actor, just sound and recovery.
    /* 0x0B */ GI_RECOVERY_HEART_SINGLE_TWO, // No actor, just sound and recovery.
    /* 0x0C */ GI_HEART_PIECE,
    /* 0x0D */ GI_HEART_CONTAINER,
    /* 0x0E */ GI_MAGIC_POT_SMALL, // Item above head, no animation like 0x01.
    /* 0x0F */ GI_MAGIC_POT_LARGE, // Item above head, no animation like 0x01.
    /* 0x10 */ GI_RECOVERY_HEART_SINGLE_THREE, // No actor, just sound and recovery.
    /* 0x11 */ //GI_ERROR_NOTHING_11, // Item above head, no animation like 0x01.
    /* 0x12 */ GI_RECOVERY_HEART_SINGLE_FOUR = 0x12, // No actor, just sound and recovery.
    /* 0x13 */ GI_RECOVERY_HEART_SINGLE_FIVE, // No actor, just sound and recovery.,
    /* 0x14 */ GI_BOMBS_1, // Item above head, no animation like 0x01. Bomb bag required.
    /* 0x15 */ GI_BOMBS_5, // Item above head, no animation like 0x01.
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
    /* 0x2B */ //GI_NUTS_30, // ***ERROR TEXT
    /* 0x2C */ //GI_ERROR_MAX_NUT, // ***ERROR TEXT MaxNut
    /* 0x2D */ //GI_UNK_2D, // Softlock
    /* 0x2E */ GI_BOMBCHU_20 = 0x2E,
    /* 0x2F */ //GI_ERROR_MAX_STICK, // ***ERROR TEXT MaxStick
    /* 0x30 */ //GI_ERROR_MAX_STICK_TWO, // ***ERROR TEXT MaxStick
    /* 0x31 */ //GI_ERROR_MAX_STICK_THREE, // ***ERROR TEXT MaxStick
    /* 0x32 */ GI_SHIELD_HERO = 0x32,
    /* 0x33 */ GI_SHIELD_MIRROR,
    /* 0x34 */ GI_POWDER_KEG,
    /* 0x35 */ GI_MAGIC_BEAN,
    /* 0x36 */ GI_BOMBCHUS_1,
    /* 0x37 */ GI_KOKIRI_SWORD, // ***ERROR TEXT Kokiri Sword - No text to begin with. Possible edit/patch?
    /* 0x38 */ GI_RAZOR_SWORD,
    /* 0x39 */ GI_GILDED_SWORD,
    /* 0x3A */ GI_BOMBCHUS_5,
    /* 0x3B */ GI_GREAT_FAIRY_SWORD,
    /* 0x3C */ GI_KEY_SMALL,
    /* 0x3D */ GI_KEY_BOSS,
    /* 0x3E */ GI_MAP, // Item pickup noise. Perhaps dungeon specific?
    /* 0x3F */ GI_COMPASS, // Item pickup noise. Perhaps dungeon specific?
    /* 0x40 */ //GI_ERROR_NOTHING_40, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x41 */ //GI_ERROR_NOTHING_41, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x42 */ GI_LENS_OF_TRUTH = 0x42,
    /* 0x43 */ GI_PICTOGRAPH_BOX = 0x43,
    /* 0x44 */ //GI_ERROR_PICTOGRAPH_BOX, // ***ERROR TEXT Get Item Nothing in hand - Gives pictograph box
    /* 0x45 */ //GI_ERROR_NOTHING_45, // Recovery Heart, no actor above head.
    /* 0x46 */ //GI_ERROR_NOTHING_46, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x47 */ //GI_ERROR_NOTHING_47, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x48 */ //GI_ERROR_NOTHING_48, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x49 */ //GI_ERROR_NOTHING_49, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x4A */ //GI_ERROR_NOTHING_4A, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x4B */ //GI_ERROR_NOTHING_4B, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x4C */ GI_OCARINA_OF_TIME = 0x4C,
    /* 0x4D */ //GI_ERROR_NOTHING_4D, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x4E */ //GI_ERROR_NOTHING_4E, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x4F */ //GI_ERROR_NOTHING_4F, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x50 */ GI_BOMBERS_NOTEBOOK = 0x50,
    /* 0x51 */ //GI_ERROR_YELLOW_RUPPEE, // ***ERROR TEXT Get Item Nothing in hand at first - then subsequently yellow rupee. No rupee increment.
    /* 0x52 */ GI_GOLD_SKULLTULA_SPIRIT = 0x52, // Pickup model is whacky since we usually don't have one.
    /* 0x53 */ //GI_ERROR_NOTHING_53, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x54 */ //GI_ERROR_NOTHING_54, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x55 */ GI_ODOLWAS_REMAINS = 0x55, // Also softlocks!
    /* 0x56 */ GI_GOHTS_REMAINS, // Also softlocks!
    /* 0x57 */ GI_GYORGS_REMAINS, // Also softlocks!
    /* 0x58 */ GI_TWINMOLDS_REMAINS, // Also softlocks!
    /* 0x59 */ GI_BOTTLE_POTION_RED,
    /* 0x5A */ GI_BOTTLE_EMPTY,
    /* 0x5B */ GI_POTION_RED, // If all bottles in item screen are full, it gives recovery hearts.
    /* 0x5C */ GI_POTION_GREEN,
    /* 0x5D */ GI_POTION_BLUE,
    /* 0x5E */ GI_FAIRY,
    /* 0x5F */ GI_DEKU_PRINCESS_FAIRY, // Shows Deku Princess Text but gives fairy
    /* 0x60 */ GI_BOTTLE_MILK = 0x60,
    /* 0x61 */ GI_BOTTLE_MILK_HALF, // ***ERROR TEXT Get Item Milk In Hand - Keeps Giving Bottles
    /* 0x62 */ GI_BOTTLE_FISH,
    /* 0x63 */ GI_BOTTLE_BUG,
    /* 0x64 */ GI_BOTTLE_BLUE_FIRE, // ***ERROR TEXT - Not implemented in game.
    /* 0x65 */ GI_BOTTLE_POE_TEXT, // Gives poe text but empty bottle.
    /* 0x66 */ GI_BOTTLE_BIG_POE,
    /* 0x67 */ GI_BOTTLE_SPRING_WATER, // No actor on GetItem.
    /* 0x68 */ GI_BOTTLE_HOT_SPRING_WATER, // No actor on GetItem. Doesn't activate timer
    /* 0x69 */ GI_BOTTLE_ZORA_EGG,
    /* 0x6A */ GI_BOTTLE_GOLD_DUST,
    /* 0x6B */ GI_BOTTLE_MAGIC_MUSHROOM,
    /* 0x6C */ //GI_ERROR_NOTHING_6C, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x6D */ //GI_BOTTLE_EMPTY_ERROR_TEXT,
    /* 0x6E */ GI_BOTTLE_SEAHORSE = 0x6E, // Gold Dust Actor lol
    /* 0x6F */ GI_BOTTLE_CHATEAU_ROMANI,
    /* 0x70 */ GI_BOTTLE_MYSTERY_MILK, // Activates Timer
    /* 0x71 */ GI_BOTTLE_MOLDY_MILK, // Mystery milk text followed by tatl.
    /* 0x72 */ //GI_ERROR_NOTHING_72, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x73 */ //GI_ERROR_NOTHING_73, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x74 */ //GI_ERROR_NOTHING_74, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x75 */ //GI_ERROR_NOTHING_75, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x76 */ //GI_ERROR_NOTHING_76, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x77 */ //GI_ERROR_NOTHING_77, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
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
    /* 0x90 */ //GI_ERROR_NOTHING_90, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0x91 */ GI_BOTTLE_CHATEAU_ROMANI_TWO =0x91, // Sets it in a different slot if no bottle present. Second bottle?
    /* 0x92 */ GI_BOTTLE_MILK_TWO, // Sets it in a different slot if no bottle present. Second bottle?
    /* 0x93 */ GI_BOTTLE_GOLD_DUST_TWO, // Sets it in a different slot if no bottle present. Second bottle?
    /* 0x94 */ GI_BOTTLE_MYSTERY_MILK_TWO, // Timer set to 0.
    /* 0x95 */ GI_BOTTLE_SEAHORSE_TWO, // Proper sea horse actor!
    /* 0x96 */ GI_MOONS_TEAR, // Provides a black screen after collecting in citra.
    /* 0x97 */ GI_TOWN_TITLE_DEED,
    /* 0x98 */ GI_SWAMP_TITLE_DEED,
    /* 0x99 */ GI_MOUNTAIN_TITLE_DEED,
    /* 0x9A */ GI_OCEAN_TITLE_DEED,
    /* 0x9B */ GI_SWORD_GREAT_FAIRY_STOLEN,
    /* 0x9C */ GI_SWORD_KOKIRI_STOLEN, // Text for when sword gets stolen.
    /* 0x9D */ GI_SWORD_RAZOR_STOLEN, // Text for when sword gets stolen.
    /* 0x9E */ GI_SWORD_GILDED_STOLEN, // Text for when sword gets stolen.
    /* 0x9F */ GI_SHIELD_HERO_2_STOLEN, // Code that treats this as hero's shield is unused, so take with a grain of salt
    /* 0xA0 */ GI_ROOM_KEY, // Softlocks if you go to the room
    /* 0xA1 */ GI_LETTER_TO_MAMA,
    /* 0xA2 */ //GI_ERROR_NOTHING_A2, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0xA3 */ //GI_ERROR_NOTHING_A3, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0xA4 */ //GI_ERROR_NOTHING_A4, // ***ERROR TEXT Get Item Keaton Mask if do not have.
    /* 0xA5 */ //GI_ERROR_NOTHING_A5, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0xA6 */ //GI_ERROR_NOTHING_A6, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0xA7 */ //GI_ERROR_NOTHING_A7, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory
    /* 0xA8 */ //GI_ERROR_NOTHING_A8, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xA9 */ GI_BOTTLE = 0xA9, // Bottle purchase back text.
    /* 0xAA */ GI_LETTER_TO_KAFEI,
    /* 0xAB */ GI_PENDANT_OF_MEMORIES,
    /* 0xAC */ //GI_ERROR_NOTHING_AC, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xAD */ //GI_ERROR_NOTHING_AD, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xAE */ //GI_ERROR_NOTHING_AE, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xAF */ //GI_ERROR_NOTHING_AF, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xB0 */ //GI_ERROR_NOTHING_B0, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xB1 */ //GI_ERROR_NOTHING_B1, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xB2 */ //GI_ERROR_NOTHING_B2, // ***ERROR TEXT Get Item Nothing in hand - Green Rupee with Ocarina in Inventory,
    /* 0xB3 */ //GI_ERROR_SUN_MASK_B3, // ***ERROR TEXT Get Item Sun's Mask in hand - Takes away ocarina if you have it.
    /* 0xB4 */ GI_MAP_OF_CLOCK_TOWN =0xB4,
    /* 0xB5 */ GI_MAP_OF_WOODFALL,
    /* 0xB6 */ GI_MAP_OF_SNOWHEAD,
    /* 0xB7 */ GI_MAP_OF_ROMANI_RANCH,
    /* 0xB8 */ GI_MAP_OF_GREAT_BAY,
    /* 0xB9 */ GI_MAP_OF_STONE_TOWER,
    /* 0xBA */ GI_FISHING_HOLE_PASS,
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
          char    pad_;
          u8 scene;
          ItemOverride_Type type;
          u8 flag;
      };
  } ItemOverride_Key;

  typedef union ItemOverride_Value {
      u32 all;
      struct {
          u16 itemId;
          u8  player;
          u8  looksLikeItemId;
      };
  } ItemOverride_Value;

  typedef struct ItemOverride {
      ItemOverride_Key   key;
      ItemOverride_Value value;
  } ItemOverride;

  ItemOverride ItemOverride_LookupByKey(ItemOverride_Key);
  void ItemOverride_PushDelayedOverride(u8);
  s32 ItemOverride_IsAPendingOverride(void);
  ItemOverride ItemOverride_Lookup(game::act::Actor*, u8, u8);
  void ItemOverride_PushDungeonReward(u8);
  void ItemOverride_CheckStartingItem();
  extern "C" void ItemOverride_GetItem(game::act::Actor*, game::act::Player*, s8);
  extern "C" int svcOutputDebugString(const char* string, size_t length);
}

#endif