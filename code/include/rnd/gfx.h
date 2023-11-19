#ifndef _RND_GFX_H_
#define _RND_GFX_H_

#include "common/types.h"
#include "hid.h"
#include "rnd/custom_models.h"
#include "rnd/draw.h"
#include "rnd/dungeon.h"
#include "rnd/input.h"
#include "rnd/rheap.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#include "rnd/spoiler_data.h"
#include "rnd/title_screen.h"
extern "C" {
#include <3ds/svc.h>
}

namespace rnd {
#define TICKS_PER_SEC 268123480
#define MAX_TICK_DELTA (TICKS_PER_SEC * 3)

#define UP_ARROW_CHR 24
#define DOWN_ARROW_CHR 25
#define LEFT_ARROW_CHR 27
#define RIGHT_ARROW_CHR 26
#define H_DOUBLE_ARROW_CHR 29
#define UP_SOLID_ARROW_CHR 30
#define DOWN_SOLID_ARROW_CHR 31

#define MAX_ENTRY_LINES 9
#define SCROLL_BAR_THICKNESS 2
#define SCROLL_BAR_MIN_THUMB_SIZE 4
#define COLOR_WARN RGB8(0xD1, 0xDF, 0x3C)
#define COLOR_SCROLL_BAR_BG RGB8(0x58, 0x58, 0x58)

#define COLOR_ICON_BOSS_KEY RGB8(0x20, 0xF9, 0x25)
#define COLOR_ICON_MAP RGB8(0xF9, 0x97, 0xFF)
#define COLOR_ICON_COMPASS RGB8(0x20, 0x3A, 0xF9)
#define COLOR_ICON_WOTH RGB8(0xFF, 0xF8, 0x2D)
#define COLOR_ICON_FOOL RGB8(0xFF, 0x2D, 0x4B)

#define COLOR_BUTTON_A RGB8(0xFF, 0x49, 0x3E)
#define COLOR_BUTTON_B RGB8(0xFD, 0xDD, 0x68)
#define COLOR_BUTTON_X RGB8(0x32, 0x7D, 0xFE)
#define COLOR_BUTTON_Y RGB8(0x00, 0xD0, 0x98)

  typedef enum {
    PAGE_SEEDHASH,
    PAGE_DUNGEONITEMS,
    PAGE_SPHERES,
    PAGE_ITEMTRACKER_ALL,
    PAGE_ITEMTRACKER_GROUPS,
    PAGE_ENTRANCETRACKER_ALL,
    PAGE_ENTRANCETRACKER_GROUPS,
    PAGE_OPTIONS,
  } GfxPage;

  void Gfx_Init(void);
  static u8 openingButton();
  extern "C" void Gfx_Update();
  extern "C" void Gfx_SleepQueryCallback();
  extern "C" void Gfx_AwakeCallback();

}  // namespace rnd

#endif  //_RND_GFX_H_