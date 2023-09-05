#include "rnd/input.h"
#include "common/debug.h"
#include "hid.h"
#include "utils.h"
#include "z3d/z3DVec.h"
extern "C" {
#include <3ds/svc.h>
}
namespace rnd {
  u32 GetCurrentPadState(void) {
    u32 hid_shared_mem = *(u32*)(0x007b2d34);
    return *(volatile u32*)(hid_shared_mem + 0x1C);
  }
#define HID_PAD (GetCurrentPadState())

  InputContext rInputCtx = {};

  // Needed for menus external to the game for spoiler logs.
  void Input_Update() {
    rInputCtx.cur.val = real_hid->pad.pads[real_hid->pad.index].curr.val;
    rInputCtx.pressed.val = (rInputCtx.cur.val) & (~rInputCtx.old.val);
    rInputCtx.up.val = (~rInputCtx.cur.val) & (rInputCtx.old.val);
    rInputCtx.old.val = rInputCtx.cur.val;
  }

  u32 buttonCheck(u32 key) {
    for (u32 i = 0x26000; i > 0; i--) {
      if (key != real_hid->pad.pads[real_hid->pad.index].curr.val)
        return 0;
    }
    return 1;
  }

  u32 Input_WaitWithTimeout(u32 msec, u32 closingButton) {
    u32 pressedKey = 0;
    u32 key = 0;
    u32 n = 0;
    u32 startingButtonState = HID_PAD;

    // Wait for no keys to be pressed
    while (HID_PAD && (msec == 0 || n <= msec)) {
      svcSleepThread(reinterpret_cast<s64>(1 * 1000 * 1000LL));
      n++;

      // If the player presses the closing button while still holding other buttons, the menu closes
      // (useful for buffering);
      u32 tempButtons = HID_PAD;
      if (tempButtons != startingButtonState && buttonCheck(tempButtons)) {
        if (tempButtons & closingButton) {
          break;
        } else {
          startingButtonState = tempButtons;
        }
      }
    }

    if (msec != 0 && n >= msec) {
      return 0;
    }

    do {
      // Wait for a key to be pressed
      while (!HID_PAD && (msec == 0 || n < msec)) {
        svcSleepThread(1 * 1000 * 1000LL);
        n++;
      }

      if (msec != 0 && n >= msec) {
        return 0;
      }

      key = HID_PAD;

      // Make sure it's pressed
      pressedKey = buttonCheck(key);
    } while (!pressedKey);

    return key;
  }

  u32 Input_Wait(void) {
    return Input_WaitWithTimeout(0, 0);
  }
}  // namespace rnd
