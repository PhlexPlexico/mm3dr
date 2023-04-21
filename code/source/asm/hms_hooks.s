.arm
.text

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global hook_OverrideHMSDekuMask
hook_OverrideHMSDekuMask:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x78
    bl ItemOverride_GetSoHItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideHMSItemID
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    cpy r0,r5
    b 0x41D01C
noOverrideHMSItemID:
    cpy r0,r5
    bl 0x233BEC
    b 0x41D01C

.global hook_OverrideHMSBombers
hook_OverrideHMSBombers:
    push {r0-r12, lr}
    cpy r0,r6
    mov r1,#0x0
    mov r2,#0x50
    bl ItemOverride_GetSoHItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideHMSBomber
    push {r0-r12, lr}
    cpy r0,r5
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    b 0x186AD4
noOverrideHMSBomber:
    orr r1,r1,r2
    b 0x186AD0

