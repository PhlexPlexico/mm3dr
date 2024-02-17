#ifndef _RND_ITEM_EFFECT_H_
#define _RND_ITEM_EFFECT_H_

// #include "icetrap.h"

#include "game/common_data.h"
#include "rnd/settings.h"
namespace rnd {
  void ItemEffect_None(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_FullHeal(game::CommonData* comData, s16 arg1, s16 arg2);
  // void give_triforce_piece(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveGiantsWallet(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveGildedSword(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveRazorSword(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveKokiriSword(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveBottle(game::CommonData* comData, s16 bottleItemId, s16 arg2);
  void ItemEffect_GiveDungeonItem(game::CommonData* comData, s16 mask, s16 dungeonId);
  void ItemEffect_GiveSmallKey(game::CommonData* comData, s16 dungeonId, s16 arg2);
  void ItemEffect_GiveDefense(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveMagic(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveSkulltula(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveDoubleMagic(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveProgressiveMagic(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveGreatSpin(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveDoubleDefense(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveOcarina(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveSong(game::CommonData* comData, s16 questBit, s16 arg2);
  void ItemEffect_GiveUpgrade(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_IceTrap(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_BeanPack(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_FillWalletUpgrade(game::CommonData* comData, s16 arg1, s16 arg2);
  void ItemEffect_GiveRemains(game::CommonData* comData, s16 mask, s16 arg2);
  void ItemEffect_GiveMask(game::CommonData* comData, s16 mask, s16 arg2);
  void ItemEffect_GiveTradeItem(game::CommonData* comData, s16 mask, s16 arg2);
}  // namespace rnd

#endif  //_ITEM_EFFECT_H_