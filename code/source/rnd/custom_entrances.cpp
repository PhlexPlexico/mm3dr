#include "rnd/custom_entrances.h"

namespace rnd {
  extern "C" {
  bool SceneEntranceOverride() {
    game::CommonData& cdata = game::GetCommonData();
    game::GlobalContext* gctx = GetContext().gctx;
    bool didWarp = false;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    rnd::util::Print("%s: Our next entrance is %#08x\n", __func__, gctx->next_entrance);
#endif
    if (gctx->next_entrance == 0x1C04 && gSettingsContext.skipMikauCutscene) {
      gctx->next_entrance = 0x6890;
      cdata.sub13s[0].entrance_index = 0x6890;
      didWarp = true;
    } else if (gctx->next_entrance == 0x1C05 && gSettingsContext.skipDarmaniCutscene) {
      gctx->next_entrance = 0x9610;
      cdata.sub13s[0].entrance_index = 0x9610;
      didWarp = true;
    } else if (gctx->next_entrance == 0x1C19 && gSettingsContext.skipHMSCutscenes) {
      gctx->next_entrance = 0xc060;
      cdata.sub13s[0].entrance_index = 0xc060;
      didWarp = true;
      // Re-enable the sound track.
      game::sound::ControlStream(game::sound::StreamPlayer::DEFAULT_PLAYER, 1, 1);
      game::sound::PlayStream(game::sound::StreamId::NA_BGM_CLOCK_TOWER, game::sound::StreamPlayer::DEFAULT_PLAYER);
    } else if (gctx->next_entrance == 0x1C01 && gSettingsContext.skipHMSCutscenes) {
      gctx->next_entrance = 0xC020;
      cdata.sub13s[0].entrance_index = 0xC020;
      didWarp = true;
      // Re-enable the sound track.
      game::sound::ControlStream(game::sound::StreamPlayer::DEFAULT_PLAYER, 1, 1);
      game::sound::PlayStream(game::sound::StreamId::NA_BGM_CLOCK_TOWER, game::sound::StreamPlayer::DEFAULT_PLAYER);
    }

    if (didWarp)
      gctx->field_C529_one_to_clear_input = 0x14;
    return didWarp;
  }

  void ForceTempleFlags() {
    game::PersistentSceneCycleFlags* cycleFlags = game::GetPersistentCycleStruct();
    cycleFlags[(u32)game::SceneId::WoodfallTemple].switch1 = 0xFFFFFFFF;
    cycleFlags[(u32)game::SceneId::SnowheadTemple].switch1 = 0xFFFFFFFF;
    cycleFlags[(u32)game::SceneId::GreatBayTemple].switch1 = 0xFFFFFFFF;
    cycleFlags[(u32)game::SceneId::StoneTowerTemple].switch1 = 0xFFFFFFFF;
    cycleFlags[(u32)game::SceneId::StoneTowerTempleInverted].switch1 = 0xFFFFFFFF;
  }
  }

}  // namespace rnd