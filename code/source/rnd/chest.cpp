#include "rnd/chest.h"
#include "rnd/item_table.h"

namespace rnd {
  extern "C" {
  game::actors::EnBoxType Chest_OverrideSize(game::actors::En_Box* actor, game::GlobalContext* gctx) {
    if (gSettingsContext.chestSize == 0) {
      return (game::actors::EnBoxType)0xFF;
    }
    s16 gid = (actor->dyna.params << 0x14) >> 0x19;
    game::SceneId scene = gctx->scene;
    ItemOverride override = ItemOverride_Lookup((game::act::Actor*)&actor->dyna, (u16)scene, gid);
    if (override.key.all != 0) {
      ItemRow* itemToBeGiven = ItemTable_GetItemRow(override.value.getItemId);
      if (itemToBeGiven->chestType == ChestType::WOODEN_SMALL) {
        return game::actors::EnBoxType::ENBOX_TYPE_SMALL;
      } else if (itemToBeGiven->chestType == ChestType::WOODEN_BIG) {
        return game::actors::EnBoxType::ENBOX_TYPE_BIG;
      } else if (itemToBeGiven->chestType == ChestType::DECORATED_BIG) {
        return game::actors::EnBoxType::ENBOX_TYPE_BIG_ORNATE;
      }
    } else {
      return (game::actors::EnBoxType)0xFF;
    }
    return (game::actors::EnBoxType)0xFF;
  }
  u8 Chest_IsOverrideEnabled(game::actors::En_Box* actor, u16 chestType) {
    s16 gid = (actor->dyna.params << 0x14) >> 0x19;
    if (gid == 0x3C && gSettingsContext.chestSize == 0)
      return false;
    if (gid == 0x3C && gSettingsContext.chestSize == 1 &&
        (chestType == (u16)game::actors::EnBoxType::ENBOX_TYPE_SMALL ||
         chestType == (u16)game::actors::EnBoxType::ENBOX_TYPE_SMALL_ROOM_CLEAR ||
         chestType == (u16)game::actors::EnBoxType::ENBOX_TYPE_SMALL_SWITCH_FLAG))
      return true;
    else if (chestType == (u16)game::actors::EnBoxType::ENBOX_TYPE_SMALL ||
              chestType == (u16)game::actors::EnBoxType::ENBOX_TYPE_SMALL_ROOM_CLEAR ||
              chestType == (u16)game::actors::EnBoxType::ENBOX_TYPE_SMALL_SWITCH_FLAG)
      return true;
    else
      return false;
  }
  }

}  // namespace rnd