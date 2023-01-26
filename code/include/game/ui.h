#ifndef _GAME_UI_H
#define _GAME_UI_H

#include <algorithm>
#include <string_view>

#include "common/flags.h"
//#include "common/span.h"
#include "common/types.h"
#include "z3d/z3DVec.h"

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
  /// Check whether the specified screen is active and not closing.
  bool CheckCurrentScreen(ScreenType screen);
  ScreenContext& GetScreenContext();

  enum class PaneType : u16 {
    Null = 0,
    Type1 = 1,
    Rect = 2,
    Text = 3,
    Pane = 4,
    PaneEx = 5,
    Pane2 = 6,
    Pane2Ex = 7,
  };

  template <typename T>
  struct Array {
    T* data;
    size_t size;

    auto begin() const { return data; }
    auto end() const { return data + size; }
    explicit operator bool() const { return data != nullptr; }
    auto& operator[](size_t index) { return data[index]; }
    const auto& operator[](size_t index) const { return data[index]; }
  };

  class Pane {
  public:
    virtual ~Pane();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void getVec4(z3dVec4f* vec, z3d_nn_math_MTX34* mtx);
    virtual void m6();
    virtual void m7();

    PaneType GetType() const { return type; }
    const char* GetName() const { return name; }

  private:
    PaneType type;
    const char* name;
  };
  static_assert(sizeof(Pane) == 0xC);

  class PaneNull : public Pane {
  public:
    z3dVec3f translate;
  };
  static_assert(sizeof(PaneNull) == 0x18);

  class Pane1 : public Pane {
  public:
    z3dVec3f translate;
    float z_multiplier;
  };
  static_assert(sizeof(Pane1) == 0x1C);

  class PaneRect : public Pane {
  public:
    z3dVec3f translate;
    float width, height;
  };
  static_assert(sizeof(PaneRect) == 0x20);

  class TextSprite : public Pane {
  public:
    u8 internal[0x300];
  };
  static_assert(sizeof(TextSprite) == 0x30C);

  struct PaneExArg {
    z3dVec3f translate;
    float width, height;
    z3dVec2f rotate;
    z3dVec2f scale;
    u16 a;
    u16 b;
    z3dVec4f colors[4];
  };
  static_assert(sizeof(PaneExArg) == 0x68);

  class PaneEx : public Pane {
  public:
    bool enable_translate;
    void* field_10;
    PaneExArg arg;
  };
  static_assert(sizeof(PaneEx) == 0x7C);

  struct WidgetPos {
    enum class Flag : u32 {
      Visible = 1,

      DefaultTranslateX = 0x100,
      DefaultTranslateY = 0x200,
      DefaultTranslateZ = 0x400,

      DefaultScaleX = 0x800,
      DefaultScaleY = 0x1000,
      DefaultScaleZ = 0x2000,

      DefaultRotateX = 0x4000,
      DefaultRotateY = 0x8000,
      DefaultRotateZ = 0x10000,

      Visible2 = 0x20000,

      DefaultField24_X = 0x40000,
      DefaultField24_Y = 0x80000,

      DefaultField2C_X = 0x100000,
      DefaultField2C_Y = 0x200000,

      DefaultField34 = 0x400000,

      DefaultColorR = 0x800000,
      DefaultColorG = 0x1000000,
      DefaultColorB = 0x2000000,
      DefaultColorA = 0x4000000,
      // alias for DefaultColorA
      DefaultOpacity = 0x4000000,
    };

    bool IsVisible() const { return flags.IsSet(Flag::Visible); }

    void SetVisible(bool visible) {
      if (IsVisible() == visible)
        return;
      flags.Set(Flag::Visible, visible);
      ValueChanged(Flag::Visible2, visible, true);
    }

    void SetOpacity(float opacity) { Set(&color.w, opacity, Flag::DefaultOpacity, 1.0f); }

    void AddOpacity(float delta, float min = 0.0f, float max = 1.0f) {
      SetOpacity(std::clamp(color.w + delta, min, max));
    }

    void SetTranslateX(float x) { Set(&translate.x, x, Flag::DefaultTranslateX, 0.0f); }
    void SetTranslateY(float y) { Set(&translate.y, y, Flag::DefaultTranslateY, 0.0f); }
    void SetTranslateZ(float z) { Set(&translate.z, z, Flag::DefaultTranslateZ, 0.0f); }

    void ScaleChanged() {
      ValueChanged(Flag::DefaultScaleX, scale.x, 1.0f);
      ValueChanged(Flag::DefaultScaleY, scale.y, 1.0f);
      ValueChanged(Flag::DefaultScaleZ, scale.z, 1.0f);
    }

    z3dVec3f translate;
    z3dVec3f scale;
    z3dVec3f field_18;
    // default (0.0, 0.0)
    z3dVec2f field_24;
    // default (1.0, 1.0)
    z3dVec2f field_2C;
    // default 0.0
    float field_34;
    // RGBA, default #ffffffff
    z3dVec4f color;
    rnd::Flags<Flag> flags;
    rnd::Flags<Flag> active_flags;

  private:
    template <typename T>
    void Set(T* variable, const T& value, Flag flag, const T& default_value) {
      if (*variable == value)
        return;
      *variable = value;
      ValueChanged(flag, value, default_value);
    }

    template <typename T>
    void ValueChanged(Flag flag, const T& value, const T& default_value) {
      flags.Set(flag);
      active_flags.Set(flag, value == default_value);
    }
  };
  static_assert(sizeof(WidgetPos) == 0x50);

  enum class WidgetType {
    Group = 0,
    Layout = 1,
    MainWidget = 2,
    Pane = 3,
  };

  class Widget {
  public:
    virtual ~Widget();
    virtual void init0(LayoutBase* layout, const char* name);
    virtual void init(LayoutBase* layout, const char* name);
    virtual void reset();
    virtual void calc(z3d_nn_math_MTX34& mtx, z3dVec4f& vec, z3d_nn_math_MTX23& mtx23, int, float time_delta);

    const char* GetName() const { return name; }
    WidgetType GetType() const;
    Widget* GetParent() const { return parent; }
    Layout* GetLayout() const { return layout; }
    Pane* GetPane() const { return pane; }

    template <typename T>
    T* AsLayout() const {
      return static_cast<T*>(layout);
    }

    Widget* GetWidget(std::string_view name);
    const Array<Widget*>& GetWidgets() const { return widgets; }

    z3d_nn_math_MTX34& GetMtx() { return mtx; }
    WidgetPos& GetPos() { return pos; }
    WidgetPos& GetOldPos() { return old_pos; }

    void PrintDebug();

  private:
    LayoutBase* layout_for_root_widget;
    Widget* parent;
    u32 parent_idx_maybe;
    const char* name;
    Array<Widget*> widgets;
    void* field_1C;
    Layout* layout;
    u16 main_widget_idx;
    u16 field_26;
    Pane* pane;
    z3dVec4f pane_vec;
    WidgetPos pos;
    WidgetPos old_pos;
    bool initialised;
    bool flag40_set;
    bool field_DE;
    bool field_DF;
    z3d_nn_math_MTX34 mtx;
    z3d_nn_math_MTX23 mtx2;
    z3dVec4f vec4;
    void* field_138;
  };
  static_assert(sizeof(Widget) == 0x13C);

  class MainWidget {
  public:
    virtual ~MainWidget();
    Widget widget;
  };

  class AnimEntry {
  public:
    virtual ~AnimEntry();

    ResAnimEntry* GetData() { return data; }

  private:
    ResAnimEntry* data;
  };

  class Anim {
  public:
    virtual ~Anim();

    const char* GetName() const { return name; }
    Array<AnimEntry*>& GetEntries() { return entries; }

  private:
    float fps = 60.0;
    const char* name = nullptr;
    int min_frame = 0;
    Array<AnimEntry*> entries;
  };
  static_assert(sizeof(Anim) == 0x18);

  class AnimPlayer {
  public:
    virtual ~AnimPlayer();

    void Play(Anim* anim, float frame = 0.0, bool loop = false);
    void SetAnimAndPause(Anim* anim, float frame);
    // The current play state (playing/paused and frame) is kept.
    void ChangeAnim(Anim* anim);
    void Stop();
    void Reset();
    void Pause() { m_playing = false; }
    void Resume() { m_playing = true; }

    bool IsPlaying() const { return m_playing; }

    const char* GetName() const { return m_name; }
    Anim* GetAnim() const { return m_anim; }

    float GetFrame() const { return m_frame; }
    void SetFrame(float frame);
    float GetSpeed() const { return m_speed; }
    void SetSpeed(float speed) { m_speed = speed; }

  private:
    const char* m_name = nullptr;
    bool m_playing = false;
    bool m_loop = false;
    bool m_xa = false;
    Anim* m_anim = nullptr;
    float m_frame = 0.0;
    float m_speed = 1.0;
  };
  static_assert(sizeof(AnimPlayer) == 0x18);

  class LayoutClass {
  public:
    virtual ~LayoutClass();

    const char* GetName() const { return name; }
    Anim* GetAnim(std::string_view name) const;
    // tcb::span<Anim> GetAnims() const { return {anims, num_anims}; }

  private:
    u16 package_idx;
    u16 layout_id;
    ResLayout* res_layout;
    u32 res_layout_size;
    u16 num_panes;
    u16 num_anims;
    Anim* anims;
    const char* name;
    Allocator* allocator;
    PaneFactory* pane_factory;
  };
  static_assert(sizeof(LayoutClass) == 0x24);

  class LayoutBase {
  public:
    virtual ~LayoutBase();
    virtual void init(LayoutClass*, MainWidget** main_widgets, int num_main_widgets, AnimPlayer** players,
                      int num_players, const char* name);
    virtual void m3();
    virtual void calc(z3d_nn_math_MTX34& mtx, z3dVec4f& vec, z3d_nn_math_MTX23& mtx2, int, float time_delta);

    void calc(float time_delta = 0.033333);

    const char* GetName() const { return name; }
    LayoutClass& GetCl() const { return *cl; }
    Widget* GetRootWidget() { return &root_widget; }
    const Array<Widget*>& GetWidgets() const { return widgets; }
    const Array<AnimPlayer*>& GetAnimPlayers() const { return players; }
    AnimPlayer* GetAnimPlayer(std::string_view name) const;
    Anim* GetAnim(std::string_view name) const { return cl->GetAnim(name); }
    Widget* GetWidget(std::string_view name);
    Pane* GetPane(std::string_view name) const;

  private:
    LayoutClass* cl;
    Widget root_widget;
    Array<Widget*> main_widgets;
    Array<AnimPlayer*> players;
    Array<Widget*> widgets;
    Array<Pane*> panes;
    u8 field_164;
    const char* name;
  };
  static_assert(sizeof(LayoutBase) == 0x16C);

  class Layout : public LayoutBase {
  public:
    // Usually called from the calc function to detect on-screen button presses and update button
    // state accordingly.
    virtual void HandleTouch(bool a, bool b, bool c, ScreenContext& ctx, int d, float time_delta, float x, float y);
    virtual void m6();
    virtual void DoInit();
    virtual void m8();
    virtual void m9();

  private:
    void* field_16C;
  };
  static_assert(sizeof(Layout) == 0x170);

}  // namespace game::ui

#endif