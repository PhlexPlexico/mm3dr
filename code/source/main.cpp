#include "common/advanced_context.h"
#include "game/context.h"
#include "game/sound.h"
#include "game/states/state.h"
#include "z3d/z3Dvec.h"
namespace rnd
{
  void Init(Context &context)
  {
    game::sound::PlayEffect(game::sound::EffectId::NA_SE_SY_PREDEMO_OMEN);
    context.has_initialised = true;
  }
  extern "C"
  {
    /*char* fake_heap_start;
    char* fake_heap_end;
    extern void (*__init_array_start[])(void) __attribute__((weak));
    extern void (*__init_array_end[])(void) __attribute__((weak));*/
    void calc(game::State *state)
    {
      Context &context = GetContext();
      context.gctx = nullptr;

      if (!context.has_initialised && state->type == game::StateType::FirstGame)
        Init(context);
      if (state->type != game::StateType::Play)
        return;
      //
      context.gctx = static_cast<game::GlobalContext*>(state);
      //castContext(context, state);
      return;
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
