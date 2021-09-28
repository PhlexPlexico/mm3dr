.arm
.text

@ .global hook_Start
@ hook_Start:
@     push {r0-r12, lr}
@     bl _start
@     pop {r0-r12, lr}
@     b 0x0103ECC

.global hook_MainLoop
hook_MainLoop:
    push {r0-r12, lr}
    bl calc
    pop {r0-r12, lr}
    ldr r1, [r0,#0x138]
    b 0x0106770


.global hook_IncomingGetItemID
hook_IncomingGetItemID:
    push {r0-r12, lr}
    @ According to Ghidra, r6 r5 r4 are the required 
    @ values needed for the GetItem header, if it isn't clear.
    cpy r0,r6
    cpy r1,r5
    cpy r2,r4
    bl ItemOverride_GetItem
    pop {r0-r12, lr}
    bx lr

.global hook_readGamePad
hook_readGamePad:
    push {r0-r12, lr}
    bl readPadInput
    pop {r0-r12, lr}
    tst r0,r1
    b 0x59ba14

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100024
    b  0x100004
