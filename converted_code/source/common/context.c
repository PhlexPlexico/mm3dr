#include "common/context.h"

void InitContext(Context* ctx) {
    ctx->has_initialised = false;
    ctx->going_back_in_time = false;
    ctx->use_fast_swim = false;
    ctx->a_press_duration = 0;
}

Context *GetContext() {
    static Context s_context;
    static int isInit = 0;
    if (!isInit) {
        InitContext(&s_context);
        isInit = 1;
    }
    return &s_context;
}

