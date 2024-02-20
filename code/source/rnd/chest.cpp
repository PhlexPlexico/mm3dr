#include "rnd/chest.h"
#include "rnd/item_table.h"

namespace rnd {
  extern "C" {
  game::actors::EnBoxType Chest_OverrideSize(game::actors::En_Box* actor, game::GlobalContext* gctx) {
    // First check to see if setting is enabled.
    // TODO: Create setting
    if (gSettingsContext.chestSize == 0) {
      return (game::actors::EnBoxType)0xFF;
    }
    s16 gid = (actor->dyna.params << 0x14) >> 0x19;
    game::SceneId scene = gctx->scene;
    ItemOverride override = ItemOverride_Lookup((game::act::Actor*)&actor->dyna, (u16)scene, gid);
    game::actors::EnBoxType boxType = (game::actors::EnBoxType)(actor->dyna.params >> 0xC);
    if (override.key.all != 0) {
      ItemRow* itemToBeGiven = ItemTable_GetItemRow(override.value.getItemId);
      if (boxType == game::actors::EnBoxType::ENBOX_TYPE_SMALL || boxType == game::actors::EnBoxType::ENBOX_TYPE_BIG ||
          boxType == game::actors::EnBoxType::ENBOX_TYPE_BIG_ORNATE) {
        if (itemToBeGiven->baseItemId == 0x02) {
          return game::actors::EnBoxType::ENBOX_TYPE_SMALL;
        } else if (itemToBeGiven->baseItemId == 0x2B || itemToBeGiven->baseItemId == 0x78) {
          return game::actors::EnBoxType::ENBOX_TYPE_BIG;
        }
      } else if (boxType == game::actors::EnBoxType::ENBOX_TYPE_BIG_INVISIBLE ||
                 boxType == game::actors::EnBoxType::ENBOX_TYPE_SMALL_INVISIBLE) {
        if (itemToBeGiven->baseItemId == 0x02) {
          boxType = game::actors::EnBoxType::ENBOX_TYPE_SMALL_INVISIBLE;
          return game::actors::EnBoxType::ENBOX_TYPE_SMALL_INVISIBLE;
        } else if (itemToBeGiven->baseItemId == 0x2B || itemToBeGiven->baseItemId == 0x78) {
          boxType = game::actors::EnBoxType::ENBOX_TYPE_BIG_INVISIBLE;
          return game::actors::EnBoxType::ENBOX_TYPE_BIG_INVISIBLE;
        }
      } else if (boxType == game::actors::EnBoxType::ENBOX_TYPE_BIG_ROOM_CLEAR ||
                 boxType == game::actors::EnBoxType::ENBOX_TYPE_SMALL_ROOM_CLEAR) {
        if (itemToBeGiven->baseItemId == 0x02) {
          return game::actors::EnBoxType::ENBOX_TYPE_SMALL_ROOM_CLEAR;
        } else if (itemToBeGiven->baseItemId == 0x2B || itemToBeGiven->baseItemId == 0x78) {
          return game::actors::EnBoxType::ENBOX_TYPE_BIG_ROOM_CLEAR;
        }
      } else if (boxType == game::actors::EnBoxType::ENBOX_TYPE_SMALL_SWITCH_FLAG ||
                 boxType == game::actors::EnBoxType::ENBOX_TYPE_BIG_SWITCH_FLAG) {
        if (itemToBeGiven->baseItemId == 0x02) {
          return game::actors::EnBoxType::ENBOX_TYPE_SMALL_SWITCH_FLAG;
        } else if (itemToBeGiven->baseItemId == 0x2B || itemToBeGiven->baseItemId == 0x78) {
          return game::actors::EnBoxType::ENBOX_TYPE_BIG_SWITCH_FLAG;
        }
      }
    } else {
      return (game::actors::EnBoxType)0xFF;
    }
    return (game::actors::EnBoxType)0xFF;
  }
  }

}  // namespace rnd