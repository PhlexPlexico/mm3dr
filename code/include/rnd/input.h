#ifndef _RND_INPUT_H
#define _RND_INPUT_H

#include "hid.h"
#include "z3d/z3DVec.h"

namespace rnd {
  typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
  } InputContext;

  void Input_Update(void);
  u32 Input_WaitWithTimeout(u32 msec, u32 closingButton);
  u32 Input_Wait(void);

// Use the shared game HID.
#define real_hid_addr 0x007B2D34
#define real_hid (*(hid_mem_t**)real_hid_addr)

  extern "C" InputContext rInputCtx;

}  // namespace rnd
#endif