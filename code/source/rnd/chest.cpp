#include "rnd/chest.h"
#include "rnd/item_table.h"

namespace rnd {
  extern "C" {
  game::actors::EnBoxType Chest_OverrideSize(game::actors::En_Box* actor, game::GlobalContext* gctx, s16 gid) {
    // First check to see if setting is enabled.
    // TODO: Create setting
    if (gSettingsContext.chestSize == 0) {
      return (game::actors::EnBoxType)0xFF;
    }
    game::SceneId scene = gctx->scene;
    ItemOverride override = ItemOverride_Lookup((game::act::Actor*)&actor->dyna, (u16)scene, gid);
    if (override.key.all != 0) {
      ItemRow* itemToBeGiven = ItemTable_GetItemRow(override.value.getItemId);
      if (actor->chest_type == game::actors::EnBoxType::ENBOX_TYPE_SMALL ||
          actor->chest_type == game::actors::EnBoxType::ENBOX_TYPE_BIG ||
          actor->chest_type == game::actors::EnBoxType::ENBOX_TYPE_BIG_ORNATE) {
        if (itemToBeGiven->baseItemId == 0x02)
          return game::actors::EnBoxType::ENBOX_TYPE_SMALL;
        else if (itemToBeGiven->baseItemId == 0x2B || itemToBeGiven->baseItemId == 0x78)
          return game::actors::EnBoxType::ENBOX_TYPE_BIG;
      } else if (actor->chest_type == game::actors::EnBoxType::ENBOX_TYPE_BIG_INVISIBLE ||
                 actor->chest_type == game::actors::EnBoxType::ENBOX_TYPE_SMALL_INVISIBLE) {
        if (itemToBeGiven->baseItemId == 0x02)
          return game::actors::EnBoxType::ENBOX_TYPE_SMALL_INVISIBLE;
        else if (itemToBeGiven->baseItemId == 0x2B || itemToBeGiven->baseItemId == 0x78)
          return game::actors::EnBoxType::ENBOX_TYPE_BIG_INVISIBLE;
      }
    } else {
      return (game::actors::EnBoxType)0xFF;
    }
    return (game::actors::EnBoxType)0xFF;
  }
  }

}  // namespace rnd