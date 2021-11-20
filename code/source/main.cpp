#include "common/advanced_context.h"
#include "game/common_data.h"
#include "game/context.h"
#include "game/message.h"
#include "game/actorresource.h"
#include "game/sound.h"
#include "game/states/state.h"
#include "game/ui.h"
#include "rnd/icetrap.h"
#include "rnd/item_override.h"
#include "rnd/rheap.h"
#include "z3d/z3Dvec.h"

#ifdef ENABLE_DEBUG
#include "common/debug.h"
extern "C" {
  
  #include <3ds/svc.h>
}
#endif

namespace rnd {
  void Init(Context &context) {
    // XXX: Temp switch to ensure patch is running.
    
    rHeap_Init();
    ItemOverride_Init();
    // TODO: Maybe make this an option?
    game::act::FixSpeedIssues();
    game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_CLEAR1);
    context.has_initialised = true;
  }
  extern "C" {

  /*char* fake_heap_start;
    char* fake_heap_end;
    extern void (*__init_array_start[])(void) __attribute__((weak));
    extern void (*__init_array_end[])(void) __attribute__((weak));*/
  void calc(game::State *state) {
    Context &context = GetContext();
    context.gctx = nullptr;
    
    if (!context.has_initialised && state->type == game::StateType::FirstGame)
      Init(context);
    if (state->type != game::StateType::Play)
      return;
    context.gctx = static_cast<game::GlobalContext *>(state);
    
    // Before calling let's be absolutely sure we have the player available.
    #ifdef ENABLE_DEBUG
    if(context.gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZL)) {
      game::act::Player* link = context.gctx->GetPlayerActor();
      if(link) {
        //game::PlayMessagePassSound();
        //GlobalContext::SpawnActor(act::Id id, u16 rx, u16 ry, u16 rz, u16 param, z3dVec3f pos);
        context.gctx->SpawnActor((game::act::Id)0x1F, 0, 0, 0, 0, link->pos.pos);
        //auto* actor = context.gctx->SpawnActor(link, (game::act::Id)actorId, 0, link->angle, 0, 0, link->pos.pos);
        
        //link->projectile_actor = actor;
        //context.gctx->ShowMessage(0x9c, link);
        rnd::util::Print("Our actor id is %#05x\n", 0);

        //game::GiveItemWithEffect(0xB9);
        // svcOutputDebugString("This is our talk actor ", 23);
        //rnd::util::GetPointer<void(game::GlobalContext*, int msgid, int)>(0x21BAFC)(context.gctx, 0x0020, 0x0);
        // svcOutputDebugString((const char*)link->talk_actor->id, sizeof(char));
        // svcOutputDebugString("\n", 2);


      }
    }
    #endif
    if(context.gctx->GetPlayerActor())
      ItemOverride_Update();
    return;
  }
  void readPadInput() {
    auto *gctx = GetContext().gctx;
    if (!gctx || gctx->type != game::StateType::Play)
      return;

    const bool zr = gctx->pad_state.input.buttons.IsSet(game::pad::Button::ZR);
    const bool start = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Start);
    const bool select = gctx->pad_state.input.new_buttons.IsSet(game::pad::Button::Select);
    if (!zr && select) {
      game::ui::OpenScreen(game::ui::ScreenType::Masks);
      return;
    }
      
    if (start && !zr) {
      game::ui::OpenScreen(game::ui::ScreenType::Items);
      return;
    }
      
    if (zr && start) {
      if (game::GetCommonData().save.inventory.collect_register.bombers_notebook != 0)
        game::ui::OpenScreen(game::ui::ScreenType::Schedule);
      else game::ui::OpenScreen(game::ui::ScreenType::Items);
      return;
    }
      
    if (zr && select) {
      // Clear map screen type. (Needed because the screen could be in "soaring" mode.)
      util::Write<u8>(game::ui::GetScreen(game::ui::ScreenType::Map), 0x78E, 0);
      game::ui::OpenScreen(game::ui::ScreenType::Map);
      gctx->pad_state.input.buttons.Clear(game::pad::Button::Select);
      gctx->pad_state.input.new_buttons.Clear(game::pad::Button::Select);
      return;
    }
  }
  /*void _start(void)
    {
      // Just in case something needs to be dynamically allocated...
      static char s_fake_heap[0x80000];
      fake_heap_start = &s_fake_heap[0];
      fake_heap_end = &s_fake_heap[sizeof(s_fake_heap)];

      for (size_t i = 0; i < size_t(__init_array_end - __init_array_start); i++)
        __init_array_start[i]();
    }*/
  }

}
