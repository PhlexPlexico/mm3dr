#include "common/utils.h"
#include "game/message.h"
#include "game/ui.h"

#ifndef _GAME_UI_GEARSCREEN_H
#define _GAME_UI_GEARSCREEN_H

namespace game::ui::screens {
  struct GearScreen {
    Screen* screen;
    int press_handler;
    u16 field_8;
    u16 field_A;
    void* subMenuTitle;
    void* subMenuUpCollect;
    void* menuCollect;
    void* commonBottomBg;
    void* btn_return_top_l;
    void* btn_return;
    void* btn_option_l;
    void* main_player;
    void* in_menu_collect_anim;
    void* out_menu_collect_anim;
    u8 gap_34[240];
    int field_124;
    int field_128;
    int field_12C;
    ItemIcon* cursorItemCollect;
    ItemIcon* icon_event00_l;
    ItemIcon* icon_event01_l;
    ItemIcon* icon_event02_l;
    ItemIcon* icon_event03_l;
    ItemIcon* icon_shadowgraph_box_l;
    ItemIcon* icon_purse_l;
    ItemIcon* icon_bomb_bag_l;
    ItemIcon* icon_arrow_l;
    ItemIcon* icon_sword_l;
    ItemIcon* icon_shield_l;
    ItemIcon* icon_boss00_l;
    ItemIcon* icon_boss02_l;
    ItemIcon* icon_boss01_l;
    ItemIcon* icon_boss03_l;
    ItemIcon* icon_schedule_l;
    ItemIcon* icon_okarina_l;
    ItemIcon* icon_trumpet_l;
    ItemIcon* icon_drum_l;
    ItemIcon* icon_guitar_l;
    ItemIcon* icon_f_tickets_l;
    ItemIcon* heart_pieces_l;
    void* frame_deformation_player;
    void* blink_picture_g;
    void* small_picture_g;
    u8 field_194;
    u8 cursorIndex;  // Possible Index For Selected Item on Gear Screen
    u8 field_196;
    u8 field_197;
    int pressed_btn_option;
    int field_19C;
    int field_1A0;
    u8 has_opened_option_menu;
    u8 gap_1a5[3];
  };
  static_assert(sizeof(GearScreen) == 0x1A8);
  static_assert(offsetof(GearScreen, press_handler) == 0x00004);

  GearScreen* GetGearScreen();
}  // namespace game::ui::screens

#endif