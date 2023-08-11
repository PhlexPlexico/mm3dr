#include "rnd/custom_message.h"

/*----- Custom Message Declarations -----*/
CustomMessage iceTrapMsg;
CustomMessage kokiriSwordMsg;
/*----- Custom Message Declarations -----*/

typedef enum {
  blank = 0x00,
  aButton,
  bButton,
  xButton,
  yButton,
  lButton,
  rButton,
  startButton,
  homeButton,
  powerButton,
  dPad,
  dPadUp,
  dPadRight,
  dPadDown,
  dPadLeft,
  dPadVertical,
  dPadHorizontal,
  cPad,
  cPadUp,
  cPadRight,
  cPadDown,
  cPadLeft,
  cPadVertical,
  cPadHorizontal,
  touchI,
  touchX,
  touchY,
  touchII,
  touchItems,

  touchMasks = 0x1E,
  touchOcarina,
  touchPictobox,
  targetReticle,

  sun = 0x28,
  moon,
  oneBlock,
  twoBlock,
  threeBlock,
  touchGear,
  touchMap,
  flag,
  tatl,
  tilde,
  notebook,
  firstPerson,
  zlButton,
  zrButton,
  majora,
} iconList;

typedef enum {
  WHITE,
  RED,
  GREEN,
  BLUE,
  YELLOW,
  CYAN,
  MAGENTA,
  GREY,
  ORANGE,
  DARK_GREY,
  BLACK,
  DEFAULT,
} colList;

class MsgBuilder {
public:
  char* data;
  u16* size;

  MsgBuilder* set(CustomMessage* msg) {
    data = &msg->data[0];
    size = &msg->size;
    return this;
  }

  MsgBuilder* addChr(char chr, bool txt = false) {
    if (*size < MAX_MSG_SIZE)
      data[(*size)++] = chr;
    return this;
  }

  MsgBuilder* text(const char* txt) {
    for (u16 idx = 0; txt[idx]; idx++)
      addChr(txt[idx], true);
    return this;
  }

  MsgBuilder* addCom(char com) {
    addChr(0x7f);
    if (*size % 2)
      addChr(0x00);
    addChr(com);
    return addChr(0x00);
  }

  MsgBuilder* addCom(char com, char arg) {
    addCom(com);
    addChr(arg);
    return addChr(0x00);
  }

  MsgBuilder* col(colList c) { return addCom(0x3a, c); }  // Change text colour until used again or new box
  MsgBuilder* icon(iconList img) {
    return addCom(0x25, img);
  }  // Insert an icon. See: https://cdn.discordapp.com/attachments/896879784162918400/1138941632675328010/image.png
  MsgBuilder* delay(char time) { return addCom(0x29, time); }  // Time measured in 20ths of a second
  MsgBuilder* top() { return addCom(0x28); }                   // Applies to all boxes in message
  MsgBuilder* instant() { return addCom(0x27); }               // Applies only to current box
  MsgBuilder* newline() { return addCom(0x01); }
  MsgBuilder* newBox() {
    addCom(0x31, 0x01);
    return addCom(0x02);
  }
  MsgBuilder* end() {
    addCom(0x31, 0x00);
    return addCom(0x00);
  }
};

MsgBuilder builder;
bool init = false;

void CustomMessage_Init(void) {
  if (!init) {
    // ----- Custom Message Definitions -----
    builder.set(&iceTrapMsg)
        ->instant()
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->text("You")
        ->delay(10)
        ->newline()
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->text("are")
        ->delay(10)
        ->newline()
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->text("  a")
        ->delay(20)
        ->newline()
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->col(RED)
        ->text("  FOOL")
        ->col(WHITE)
        ->text("!")
        ->newBox()

        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->icon(blank)
        ->col(YELLOW)
        ->text("<3")
        ->end();

    builder.set(&kokiriSwordMsg)
        ->instant()
        ->text("You got the ")
        ->col(MAGENTA)
        ->text("Kokiri Sword")
        ->col(WHITE)
        ->text("!")
        ->delay(20)
        ->newline()
        ->text("Swing it with  ")
        ->icon(bButton)
        ->end();
  }

  init = true;
}
