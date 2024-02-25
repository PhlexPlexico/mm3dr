#include "rnd/custom_messages.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

#define LINE_WIDTH 260
#define ICON_WIDTH 16
#define MAJORA_ICON_WIDTH 32
#define MAX_CHAR 0x220
#define DEFAULT_WIDTH 8
#define INSTANT_FLAG 0x8000
#define REPEAT_FLAG 0x4000

// Pixel widths of printable characters (many are replaced by * which is 8 pixels)
char width[MAX_CHAR] = {
    0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 00x
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 01x
    4,  4,  6,  10, 9,  12, 10, 4,  5,  5,  8,  9,  5,  7,  4,  7,   // 02x
    9,  6,  9,  9,  10, 9,  9,  9,  9,  9,  4,  5,  8,  8,  8,  8,   // 03x
    11, 10, 10, 10, 11, 9,  9,  10, 10, 4,  6,  10, 8,  13, 11, 10,  // 04x
    10, 10, 9,  9,  9,  10, 10, 13, 9,  9,  10, 5,  7,  5,  8,  8,   // 05x
    5,  8,  9,  8,  9,  9,  5,  8,  9,  4,  5,  8,  4,  12, 9,  9,   // 06x
    9,  8,  6,  7,  5,  9,  8,  11, 8,  8,  8,  5,  4,  5,  6,  0,   // 07x
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 08x
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 09x
    0,  4,  8,  10, 8,  9,  4,  9,  6,  10, 5,  8,  7,  7,  10, 7,   // 0Ax
    4,  10, 6,  5,  5,  10, 8,  4,  4,  4,  5,  8,  9,  9,  10, 8,   // 0Bx
    10, 10, 10, 10, 11, 10, 12, 9,  9,  9,  9,  10, 5,  5,  5,  5,   // 0Cx
    11, 10, 10, 10, 10, 10, 10, 10, 10, 9,  9,  9,  9,  9,  8,  8,   // 0Dx
    8,  8,  9,  9,  8,  9,  11, 8,  9,  9,  9,  9,  5,  5,  5,  5,   // 0Ex
    9,  8,  9,  9,  9,  9,  9,  11, 9,  9,  9,  9,  9,  8,  9,  9,   // 0Fx
    10, 8,  10, 8,  11, 10, 10, 8,  8,  8,  10, 8,  10, 8,  11, 12,  // 10x
    8,  8,  9,  9,  8,  8,  9,  9,  9,  9,  9,  9,  8,  8,  10, 8,   // 11x
    10, 8,  10, 8,  8,  8,  11, 9,  8,  8,  6,  6,  8,  8,  5,  5,   // 12x
    4,  4,  10, 8,  8,  8,  10, 8,  8,  9,  6,  8,  5,  8,  8,  8,   // 13x
    8,  9,  5,  11, 9,  11, 9,  11, 9,  8,  8,  8,  8,  8,  8,  8,   // 14x
    10, 9,  11, 12, 10, 6,  8,  8,  10, 6,  9,  7,  8,  8,  9,  7,   // 15x
    9,  7,  8,  8,  9,  7,  8,  8,  8,  8,  10, 9,  8,  8,  10, 9,   // 16x
    10, 9,  10, 10, 8,  8,  8,  8,  8,  10, 8,  10, 8,  10, 8,  8,   // 17x
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 18x
    8,  8,  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 19x
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 1Ax
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 1Bx
    8,  8,  8,  8,  8,  15, 14, 8,  8,  8,  8,  8,  8,  8,  8,  8,   // 1Cx
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 1Dx
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 1Ex
    8,  8,  15, 14, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 1Fx
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,   // 20x
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  5,  8,  8,  8,  8,   // 21x
};

typedef struct {
  u16 id;
  char data[MAX_MSG_SIZE];
  u16 size;
} CustomMessage;

// Extract data less than 8 bits long from a char array without wasting bits
u8 unpackData(u8 size, u8 idx, char* data) {
  u8 i, unpacked = 0;
  for (i = 0; i < size; i++) {
    unpacked <<= 1;
    if ((data[(idx * size + i) / 8] << ((idx * size + i) % 8)) & 0x80)
      unpacked += 1;
  }
  return unpacked;
}

// Pack data less than 8 bits long into a char array without wasting bits
void packData(u8 size, u8 idx, char* data, u8 unpacked) {
  for (u8 i = size; i--;) {
    if (unpacked & 1)
      data[(idx * size + i) / 8] |= 0x80 >> ((idx * size + i) % 8);
    else
      data[(idx * size + i) / 8] &= ~(0x80 >> ((idx * size + i) % 8));
    unpacked >>= 1;
  }
}

class MsgBuilder {
public:
  char* data;
  u16* size;

  MsgBuilder* set(CustomMessage* msg) {
    data = &msg->data[0];
    size = &msg->size;
    return this;
  }

  MsgBuilder* addChr(char chr) {
    if (*size < MAX_MSG_SIZE)
      data[(*size)++] = chr;
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    else
      rnd::util::Print("Error building message: MAX_MSG_SIZE exceeded\n");
#endif
    return this;
  }

  MsgBuilder* text(const char* txt) {
    // UTF8 encoding excluding 0x00 and 0x7F
    // Many characters, especially control characters, print as `*`
    for (u16 idx = 0; txt[idx]; idx++)
      addChr(txt[idx]);
    return this;
  }

  MsgBuilder* pad(bool always) {
    if (always)
      addChr(0x00);
    if (*size % 2)
      addChr(0x00);
    return this;
  }

  MsgBuilder* addCom(char com) {
    addChr(0x7f);
    pad(false);
    addChr(com);
    return addChr(0x00);
  }

  MsgBuilder* addCom(char com, char arg) {
    addCom(com);
    addChr(arg);
    return addChr(0x00);
  }

  MsgBuilder* sound(u16 id) {
    // Must have a sufficient delay if used multiple times in one box
    addCom(0x32);
    // Has 2 extra padding bytes if not the first command in a message
    pad(*size != 4);
    addChr(id & 0xFF);
    addChr(id >> 0x8);
    addChr(0x00);
    return addChr(0x01);
  }

  MsgBuilder* filename() {
    return addCom(0x03);
  }  // 1 to 8 UTF8 characters so size highly variable
  MsgBuilder* col(char c) {
    return addCom(0x3a, c);
  }  // Change text colour until used again or new box
  MsgBuilder* icon(char img) {
    return addCom(0x25, img);
  }  // Insert an icon. See: https://cdn.discordapp.com/attachments/896879784162918400/1138941632675328010/image.png
  MsgBuilder* delay(char time) {
    return addCom(0x29, time);
  }  // Time measured in 20ths of a second
  MsgBuilder* top() {
    return addCom(0x28);
  }  // Applies to all boxes in message
  MsgBuilder* instant() {
    return addCom(0x27);
  }  // Applies only to current box
  MsgBuilder* newline() {
    return addCom(0x01);
  }
  MsgBuilder* newBox() {
    addCom(0x31, 0x01);
    return addCom(0x02);
  }
  MsgBuilder* end() {
    addCom(0x31, 0x00);
    return addCom(0x00);
  }

  void format(UnformattedMessage msg) {
    // @ - filename min: 4px max: 120px
    // # - colour change
    // & - newline
    // ^ - new box
    // $ - icon
    // % - delay
    u16 idx = 0xFFFF, lastSpaceIdx = 0;
    u16 colIdx = 0, colIdxAtLastSpace = 0;
    u16 iconIdx = 0, iconIdxAtLastSpace = 0;
    u16 delayIdx = 0, delayIdxAtLastSpace = 0;
    u16 sizeAtLastSpace = 0, resolvedChar = 0, lineLen = 0;
    bool inCol = false, inColAtLastSpace = false;
    bool lineWrap = true;
    u16 sfx = msg.sfxAndFlags & 0x3FFF;
    u8 resolvedCol = 0, resolvedIcon = 0, resolvedDelay = 0;
    *size = 0;

    if (sfx)
      sound(sfx);
    if (msg.sfxAndFlags & INSTANT_FLAG)
      instant();

    // Tingle Map Choices. Add 3 choices, 2 for maps and 1 for no thanks.
    if (msg.id >= 0x1D11 && msg.id <= 0x1D16) {
      addCom(0x2F, 3);
      // Disable line wrap to ensure text lines up with options
      lineWrap = false;
    }

    while (++idx < MAX_UNFORMATTED_SIZE && msg.text[idx]) {
      resolvedChar = msg.text[idx];

      switch (resolvedChar) {
      case '@':  // Player file name
        if (!lastSpaceIdx)
          sizeAtLastSpace = *size;
        filename();
        lineLen += 120;  // TODO: dynamically fit to actual filename?
        break;

      case '#':  // Colour marker
        if (inCol)
          col(QM_DEFAULT);
        else {
          // Abort if out of colours
          if (colIdx >= 8) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
            rnd::util::Print("Error formatting message, out of colours: %s\n", msg.text);
#endif

            return;
          }
          // Get next colour
          resolvedCol = unpackData(4, colIdx++, msg.cols);

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
          // Could be caused by not providing enough colours so provide debug message
          if (!resolvedCol)
            rnd::util::Print("Warning formatting message, colour %i is 0x00: %s\n", colIdx, msg.text);
#endif

          col(resolvedCol);
        }
        inCol = !inCol;
        break;

      case '&':  // Newline
        newline();
        lastSpaceIdx = 0;
        lineLen = 0;
        break;

      case '^':  // Newbox
        newBox();
        // New boxes have default colours so re-apply colour
        if (inCol)
          col(resolvedCol);
        // If set to repeat sfx then add to this box
        if ((msg.sfxAndFlags & REPEAT_FLAG) && sfx)
          sound(sfx);
        // New boxes lose the instant text property so re-set it
        if (msg.sfxAndFlags & INSTANT_FLAG)
          instant();

        lastSpaceIdx = 0;
        lineLen = 0;
        break;

      case '$':  // Icon marker
        if (!lastSpaceIdx)
          sizeAtLastSpace = *size;
        // Abort if out of icons
        if (iconIdx >= 8) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
          rnd::util::Print("Error formatting message, out of icons: %s\n", msg.text);
#endif

          return;
        }
        // Get next icon
        resolvedIcon = unpackData(6, iconIdx++, msg.icons);

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
        // Could be caused by not providing enough icons so provide debug message
        if (!resolvedIcon)
          rnd::util::Print("Warning formatting message, icon %i is 0x00: %s\n", iconIdx, msg.text);
#endif
        // Majora icon is wider than all other icons
        lineLen += (resolvedIcon == MAJORA_ICON) ? MAJORA_ICON_WIDTH : ICON_WIDTH;
        icon(resolvedIcon);
        break;

      case '%':  // Delay marker
        // Abort if out of delays
        if (delayIdx >= 8) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
          rnd::util::Print("Error formatting message, out of delays: %s\n", msg.text);
#endif

          return;
        }

        resolvedDelay = unpackData(6, delayIdx++, msg.delays);
        // Don't bother inserting a delay of 0 as is a waste of characters
        if (resolvedDelay)
          delay(resolvedDelay);
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
        // Could be caused by not providing enough delays so provide debug message
        else
          rnd::util::Print("Warning formatting message, delay %i is 0x00: %s\n", delayIdx, msg.text);
#endif
        break;

      case ' ':
        // Keep track of spaces for inserting line breaks
        lastSpaceIdx = idx;
        colIdxAtLastSpace = colIdx;
        iconIdxAtLastSpace = iconIdx;
        delayIdxAtLastSpace = delayIdx;
        inColAtLastSpace = inCol;
        sizeAtLastSpace = *size;
        // Don't break so can still be processed as a normal character
      default:
        if (!lastSpaceIdx)
          sizeAtLastSpace = *size;
        // Uses UTF8 encoding so convert multi-byte representations to a single number
        if (resolvedChar > 0x7F) {
          // Abort if char requires 3 or more bytes to represent in UTF8
          if (resolvedChar > 0xDF) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
            rnd::util::Print("Error formatting message, unsupported character: %s\n", msg.text);
#endif

            return;
          }
          // Extract data from 2 byte UTF8 char. Also add the first half to the message
          resolvedChar = ((msg.text[idx] & 0x1F) << 6) | (msg.text[idx + 1] & 0x3F);
          addChr(msg.text[idx++]);
        }

        addChr(msg.text[idx]);
        // Assumes all further chars will be represented by * as many up to MAX_CHAR already are
        lineLen += (resolvedChar < MAX_CHAR) ? width[resolvedChar] : DEFAULT_WIDTH;
        break;
      }

      // Replace last space with newline if necessary
      // If no space available use start of last item with width
      if (lineWrap && lineLen > LINE_WIDTH) {
        if (lastSpaceIdx) {
          idx = lastSpaceIdx;
          colIdx = colIdxAtLastSpace;
          iconIdx = iconIdxAtLastSpace;
          delayIdx = delayIdxAtLastSpace;
          inCol = inColAtLastSpace;

          lastSpaceIdx = 0;
        } else
          idx -= (resolvedChar > 0x7F) ? 2 : 1;

        *size = sizeAtLastSpace;
        newline();
        lastSpaceIdx = 0;
        lineLen = 0;
      }
    }

// Add debug message if the last colour didn't have an end marker
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
    if (inCol)
      rnd::util::Print("Warning formatting message, colour not closed: %s\n", msg.text);
#endif
    if (msg.id >= 0x1D11 && msg.id <= 0x1D16)
      addCom(0x00);
    else
      end();
  }
};

MsgBuilder builder;
CustomMessage customMsg;

volatile const UnformattedMessage rCustomMessages[512] = {0};
volatile const u32 numCustomMessageEntries = {0};

bool SetCustomMessage(u16 id, game::MessageResEntry* msgResEntry) {
  // #if defined ENABLE_DEBUG || defined DEBUG_PRINT
  //   static u16 lastId;
  //   if (id && id != lastId)
  //     rnd::util::Print("Message ID is %#06x\n", id);
  //   lastId = id;
  // #endif

  UnformattedMessage customMsgData;
  s32 start = 0, end = numCustomMessageEntries - 1, current;

  while (start <= end) {
    current = (start + end) / 2;
    // Compiler isn't happy with assigning volatile const to not so reference/dereference to get data
    customMsgData = *(UnformattedMessage*)&rCustomMessages[current];
    if (customMsgData.id < id)
      start = current + 1;
    else if (customMsgData.id > id)
      end = current - 1;
    else {
      // Only reformat message if it's different to the current formatted message
      // Message get function called multiple times per message so this is important
      if (id != customMsg.id)
        builder.set(&customMsg)->format(customMsgData);
      // Populate message entry with data from app side and the formatted message
      msgResEntry->id = customMsg.id = id;
      msgResEntry->field_2 = customMsgData.field_2;
      msgResEntry->field_4 = customMsgData.field_4;
      msgResEntry->flags = customMsgData.flags;
      msgResEntry->texts[0].offset = customMsg.data;
      msgResEntry->texts[0].length = customMsg.size;
      return true;
    }
  }

  // Didn't find id in custom messages
  return false;
}
