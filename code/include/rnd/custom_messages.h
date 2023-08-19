#ifndef _RND_CUSTOM_MESSAGES_H_
#define _RND_CUSTOM_MESSAGES_H_

#include "common/utils.h"
#include "game/message.h"

#define MAX_MSG_SIZE 512
#define MAX_UNFORMATTED_SIZE 354

bool SetCustomMessage(u16, game::MessageResEntry*);

typedef struct {
  u16 id;
  u16 field_2;
  u32 field_4;
  u32 flags;
  char text[MAX_UNFORMATTED_SIZE];
  char cols[4];
  char icons[6];
  char delays[6];
  u16 sfxAndFlags;
} UnformattedMessage;

typedef enum {
  BLANK = 0x00,
  A_BUTTON,
  B_BUTTON,
  X_BUTTON,
  Y_BUTTON,
  L_BUTTON,
  R_BUTTON,
  START_BUTTON,
  HOME_BUTTON,
  POWER_BUTTON,
  D_PAD,
  D_PAD_UP,
  D_PAD_RIGHT,
  D_PAD_DOWN,
  D_PAD_LEFT,
  P_PAD_VERTICAL,
  P_PAD_HORIZONTAL,
  C_PAD,
  C_PAD_UP,
  C_PAD_RIGHT,
  C_PAD_DOWN,
  C_PAD_LEFT,
  C_PAD_VERTICAL,
  C_PAD_HORIZONTAL,
  I_TOUCH,
  X_TOUCH,
  Y_TOUCH,
  II_TOUCH,
  ITEMS_TOUCH,

  MASKS_TOUCH = 0x1E,
  OCARINA_TOUCH,
  PICTOBOX_TOUCH,
  TARGET_RETICLE,

  SUN = 0x28,
  MOON,
  ONE_BLOCK,
  TWO_BLOCK,
  THREE_BLOCK,
  GEAR_TOUCH,
  MAP_TOUCH,
  FLAG,
  TATL,
  TILDE,
  NOTEBOOK,
  FIRST_PERSON,
  ZL_BUTTON,
  ZR_BUTTON,
  MAJORA_ICON,
} iconType;

typedef enum {
  QM_WHITE,
  QM_RED,
  QM_GREEN,
  QM_BLUE,
  QM_YELLOW,
  QM_CYAN,
  QM_MAGENTA,
  QM_GREY,
  QM_ORANGE,
  QM_DARK_GREY,
  QM_BLACK,
  QM_DEFAULT,
} colType;

#endif
