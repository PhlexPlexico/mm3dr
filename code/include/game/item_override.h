#ifndef _GAME_ITEM_OVERRIDE_H
#define _GAME_ITEM_OVERRIDE_H

#include "common/advanced_context.h"
#include "common/utils.h"
#include "game/common_data.h"
#include "z3d/z3Dvec.h"

namespace game {

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
    /* 0x11 */ GI_RUPEE_GREEN_NO_ANIMATION, // Item above head, no animation like 0x01.
    /* 0x12 */ GI_RECOVERY_HEART_SINGLE_FOUR, // No actor, just sound and recovery.
    /* 0x13 */ GI_RECOVERY_HEART_SINGLE_FIVE, // No actor, just sound and recovery.,
    /* 0x14 */ GI_BOMBS_1, // Item above head, no animation like 0x01.
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
    /* 0x2B */ GI_NUTS_30, // ***ERROR TEXT
    /* 0x2C */ GI_ERROR_MAX_NUT, // ***ERROR TEXT MaxNut
    /* 0x2D */ GI_UNK_2D, // Softlock
    /* 0x2E */ GI_BOMBCHU_20,
    /* 0x2F */ GI_ERROR_MAX_STICK, // ***ERROR TEXT MaxStick
    /* 0x30 */ GI_ERROR_MAX_STICK_TWO, // ***ERROR TEXT MaxStick
    /* 0x31 */ GI_ERROR_MAX_STICK_THREE, // ***ERROR TEXT MaxStick
    /* 0x32 */ GI_SHIELD_HERO,
    /* 0x33 */ GI_SHIELD_MIRROR,
    /* 0x34 */ GI_POWDER_KEG,
    /* 0x35 */ GI_MAGIC_BEAN,
    /* 0x36 */ GI_BOMBCHUS_1,
    /* 0x37 */ GI_ERROR_KOKIRI_SWORD, // ***ERROR TEXT Kokiri Sword
    /* 0x38 */ GI_RAZOR_SWORD,
    /* 0x39 */ GI_GILDED_SWORD,
    /* 0x3A */ GI_BOMBCHUS_5,
    /* 0x3B */ GI_UNK_3B, // Sound Like Picking Up Items such as nuts or stick. Possible item in dungeon?
    /* 0x3C */ GI_KEY_SMALL,
    /* 0x3D */ GI_KEY_BOSS,
    /* 0x3E */ GI_MAP, // Item pickup noise. Perhaps dungeon specific?
    /* 0x3F */ GI_COMPASS, // Item pickup noise. Perhaps dungeon specific?
    /* 0x40 */ GI_RUPEE_GREEN_NO_ANIMATION_TWO, // Item above head, no animation like 0x01.
    /* 0x41 */ GI_UNK_41, // Item Pickup Sound - Maybe dungeon dependent?
    /* 0x42 */ GI_UNK_42, // Item Pickup Sound - Maybe dungeon dependent?
    /* 0x43 */ GI_UNK_43, // Item Pickup Sound - Maybe dungeon dependent?
    /* 0x44 */ GI_UNK_44, // Single Green Rupee But Fairies Work?
    /* 0x45 */ GI_UNK_45,
    /* 0x46 */ GI_UNK_46,
    /* 0x47 */ GI_UNK_47,
    /* 0x48 */ GI_UNK_48,
    /* 0x49 */ GI_UNK_49,
    /* 0x4A */ GI_UNK_4A,
    /* 0x4B */ GI_UNK_4B,
    /* 0x4C */ GI_UNK_4C,
    /* 0x4D */ GI_UNK_4D,
    /* 0x4E */ GI_UNK_4E,
    /* 0x4F */ GI_UNK_4F,
    /* 0x50 */ GI_UNK_50,
    /* 0x51 */ GI_UNK_51,
    /* 0x52 */ GI_UNK_52,
    /* 0x53 */ GI_UNK_53,
    /* 0x54 */ GI_UNK_54,
    /* 0x55 */ GI_UNK_55,
    /* 0x56 */ GI_UNK_56,
    /* 0x57 */ GI_UNK_57,
    /* 0x58 */ GI_UNK_58,
    /* 0x59 */ GI_BOTTLE_POTION_RED = 0x59,
    /* 0x5B */ GI_POTION_RED = 0x5B,
    /* 0x5C */ GI_POTION_GREEN,
    /* 0x5D */ GI_POTION_BLUE,
    /* 0x5E */ GI_FAIRY,
    /* 0x60 */ GI_MILK_BOTTLE = 0x60,
    /* 0x7E */ GI_MASK_ALL_NIGHT = 0x7E,
    /* 0x80 */ GI_MASK_KEATON = 0x80,
    /* 0x82 */ GI_MASK_ROMANIS = 0x82,
    /* 0x8C */ GI_MASK_BREMEN = 0x8C,
    /* 0x9B */ GI_SWORD_GREAT_FAIRY = 0x9B,
    /* 0x9C */ GI_SWORD_KOKIRI,
    /* 0x9D */ GI_SWORD_RAZOR,
    /* 0x9E */ GI_SWORD_GILDED,
    /* 0x9F */ GI_SHIELD_HERO_2, // Code that treats this as hero's shield is unused, so take with a grain of salt
    /* 0xA1 */ GI_LETTER_TO_MAMA = 0xA1,
    /* 0xA9 */ GI_BOTTLE = 0xA9
};

  extern "C" void ItemOverride_GetItem(act::Actor*, act::Player*, s8);
}

#endif