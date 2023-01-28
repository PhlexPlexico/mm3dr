.arm
.text

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global hook_OverrideFairyItemNCT
hook_OverrideFairyItemNCT:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x40
    bl ItemOverride_GetFairyRewardItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideFairyItemIDNCT
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    cpy r0,r5
    b 0x3BECC0
noOverrideFairyItemIDNCT:
    cpy r0,r5
    b 0x3BECBC

.global hook_OverrideFairyItemWF
hook_OverrideFairyItemWF:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetFairyRewardItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideFairyItemIDWF
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    orr r1,r1,#0x2
    b 0x3becdc
noOverrideFairyItemIDWF:
    b 0x3becc0