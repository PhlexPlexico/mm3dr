// TODO: Import common_data
// #include "z3D/z3D.h"
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


#define real_hid_addr   0x10002000
#define real_hid        (*(hid_mem_t *) real_hid_addr)

extern InputContext rInputCtx;