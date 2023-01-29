.arm
.text

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global hook_OverrideFairyItem
hook_OverrideFairyItem:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x0
    bl ItemOverride_GetFairyRewardItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideFairyItemID
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    cpy r0,r4
    b 0x3becf4
noOverrideFairyItemID:
    cpy r0,r4
    b 0x3becf4