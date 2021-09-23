#ifndef _RND_ITEM_EFFECT_H_
#define _RND_ITEM_EFFECT_H_

//#include "icetrap.h"

#include "game/common_data.h"
#include "rnd/settings.h"
namespace rnd {
  void ItemEffect_None(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_FullHeal(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  // void give_triforce_piece(game::SaveData* saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveGiantsWallet(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveGildedSword(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveBottle(game::SaveData *saveCtx, s16 bottleItemId, s16 arg2);
  void ItemEffect_GiveDungeonItem(game::SaveData *saveCtx, s16 mask, s16 dungeonId);
  void ItemEffect_GiveSmallKey(game::SaveData *saveCtx, s16 dungeonId, s16 arg2);
  void ItemEffect_GiveDefense(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveMagic(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveDoubleMagic(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveOcarina(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveSong(game::SaveData *saveCtx, s16 questBit, s16 arg2);
  void ItemEffect_GiveUpgrade(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_IceTrap(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_BeanPack(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_FillWalletUpgrade(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_PlaceMagicArrowsInInventory(game::SaveData *saveCtx, s16 arg1, s16 arg2);
  void ItemEffect_GiveRemains(game::SaveData *saveCtx, s16 mask, s16 arg2);
  void ItemEffect_GiveMask(game::SaveData *saveCtx, s16 mask, s16 arg2);
}

#endif //_ITEM_EFFECT_H_