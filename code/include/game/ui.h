#ifndef _GAME_UI_H
#define _GAME_UI_H

#include <algorithm>
#include <string_view>

#include "common/flags.h"
//#include "common/span.h"
#include "common/types.h"

namespace game {
class Allocator;
}

namespace game::ui {

// Classes with known, official names:
//
// core::LayoutBuilder
// core::LayoutClass
// core::Package
// core::Project
// joker::ExtraPadCheckDialog
// joker::LayoutDrawManager
// joker::LayoutFactory
// joker::LayoutManager
// joker::TextSprite

class Layout;
class LayoutBase;
class LayoutClass;
class PaneFactory;
class PlayHud;
class ResAnimEntry;
class ResLayout;
class Screen;
struct ScreenContext;

class Font {
  u8 internal[0x14];
};

enum class ScreenType {
  Black,
  Main,
  Schedule,
  Quest,
  Gear = Quest,
  Items,
  Map,
  Masks,
  /// "Play your instrument" screen
  Ocarina,
};
Screen* GetScreen(ScreenType screen);
bool OpenScreen(ScreenType screen);

}  // namespace game::ui

#endif