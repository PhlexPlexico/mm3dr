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
    mov r2,#0x0
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
    b 0x41D018