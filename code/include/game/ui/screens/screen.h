/**
 * @file screen.h
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Edited to adjust for the randomizer.
 */
#ifndef _GAME_UI_SCREENS_SCREEN_H
#define _GAME_UI_SCREENS_SCREEN_H

#include "common/types.h"

namespace game {
  class State;
}

namespace game::ui {

  class Screen;

  struct Context {
    u8 gap_0[0x16C];
    State* game_state;
    float time_delta;
    u8 field_174;
  };
  static_assert(sizeof(Context) == 0x178);

  struct ScreenContext {
    virtual ~ScreenContext() = default;
    template <typename T>
    T* GetState() const {
      return ctx ? static_cast<T*>(ctx->game_state) : nullptr;
    }

    Context* ctx;
    /// The currently opened screen.
    Screen* active_screen = nullptr;
    /// The screen that is soon to be opened and shown.
    Screen* new_screen = nullptr;
    bool open_finished = true;
    bool close_finished = true;
  };
  static_assert(sizeof(ScreenContext) == 0x14);

  struct ScreenCaptureContext {
    u32 field_0;
    u32 state;
    u32 field_8;
    void* data;
    u32 data_size;
    u16 width;
    u16 height;
    u8 timer;
    u8 capture_type;
    u8 gap_1A[2];
    u32 field_1C;
  };
  static_assert(sizeof(ScreenCaptureContext) == 0x20);

  // A screen is the top-level component of the UI system.
  // It is responsible for orchestrating layouts and handling transitions between game menus.
  class Screen {
  public:
    virtual ~Screen() = default;
    virtual void Init(ScreenContext&) {}
    virtual void m3() {}
    virtual void PrepareOpen(ScreenContext&) {}
    virtual void m4() {}
    /// Called while opening the screen.
    /// Return true when finished.
    virtual bool CalcOpen(ScreenContext&) { return true; }
    virtual void Open(ScreenContext&) {}
    virtual void Calc(ScreenContext&) {}
    /// Called after game state calc.
    virtual void Draw(ScreenContext&) {}
    virtual void PrepareClose(ScreenContext&) {}
    /// Called while closing the screen.
    /// Return true when finished (typically, after animations have completed).
    virtual bool CalcClose(ScreenContext&) { return true; }
    virtual void Close(ScreenContext&) {}
  };
  static_assert(sizeof(Screen) == 0x4);

}  // namespace game::ui

#endif