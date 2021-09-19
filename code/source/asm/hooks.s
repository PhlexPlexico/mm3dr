.arm
.text

@ TODO: Hook into Global Context Update/Main Game Loop.
.global hook_MainLoop
hook_MainLoop:
    push {r0-r12, lr}
    bl calc
    pop {r0-r12, lr}
    ldr r1, [r0,#0x138]
    bx lr

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100024
    b  0x100004
