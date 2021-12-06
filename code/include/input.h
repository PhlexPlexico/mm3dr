#include "z3d/z3DVec.h"
#include "hid.h"

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
#define real_hid_addr   0x007b2d34
#define real_hid        (*(hid_mem_t *) real_hid_addr)

extern InputContext rInputCtx;