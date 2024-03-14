.arm
.text

.global hook_CheckTingle
hook_CheckTingle:
    push {r0-r12,lr}
    cpy r1,r6
    bl ItemOverride_CheckTingleMaps
    cmp r0,#0x1
    pop {r0-r12,lr}
    bne doNotGiveItem
    push {r0}
    mov r0,#0x0
    cmp r0,#0x0
    pop {r0}
    bx lr 
doNotGiveItem:
    b 0x2DAC3C

.global hook_CheckTingleTwo
hook_CheckTingleTwo:
    push {r0-r12,lr}
    cpy r1,r6
    bl ItemOverride_CheckTingleMaps
    cmp r0,#0x1
    pop {r0-r12,lr}
    bne doNotGiveItemTwo
    push {r0}
    mov r0,#0x0
    cmp r0,#0x0
    pop {r0}
    bx lr
doNotGiveItemTwo:
    b 0x3F6038