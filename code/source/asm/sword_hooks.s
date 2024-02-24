.arm
.text

.global hook_DoNotGiveSwordBackOnReset
hook_DoNotGiveSwordBackOnReset:
    bhi 0x1C9958 @ original instruction, if gilded sword ignore these. 
    push {r0-r12, lr}
    bl SongOfTimeSwordPlacement @ See rnd/link.cpp
    pop {r0-r12, lr}
    bx lr

.global hook_DoNotGiveSwordBackOnResetTwo
hook_DoNotGiveSwordBackOnResetTwo:
    push {r0-r12, lr}
    bl SongOfTimeSwordPlacement @ See rnd/link.cpp
    pop {r0-r12, lr}
    bx lr


.global hook_GaboraCheckExtDataNotSword
hook_GaboraCheckExtDataNotSword:
    push {r0-r12, lr}
    bl ItemOverride_GetGaboraExtData
    cmp r0, #0x0
    beq giveRazorSwordReward
    cmp r0, #0x1
    beq giveGildedSword
    pop {r0-r12,lr}
    cmp r0,r0
    bx lr
giveRazorSwordReward:
    pop {r0-r12,lr}
    cmp r0,#0xFF
    b 0x2CBB3C
giveGildedSword:
    pop {r0-r12,lr}
    cmp r0,r0
    b 0x2CBB38