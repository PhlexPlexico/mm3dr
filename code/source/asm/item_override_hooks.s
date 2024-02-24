.arm
.text

.global rActiveItemTextId
.rActiveItemTextId_addr:
    .word rActiveItemTextId

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global rActiveItemGraphicId
.rActiveItemGraphicId_addr:
    .word rActiveItemGraphicId

.global rStoredTextId
.rStoredTextId_addr:
    .word rStoredTextId

.global hook_IncomingGetItemID
hook_IncomingGetItemID:
    push {r0-r12, lr}
    @ According to Ghidra, r6 r5 r4 are the required 
    @ values needed for the GetItem header, if it isn't clear.
    cpy r0,r7
    cpy r1,r6
    cpy r2,r5
    cpy r3,r4
    bl ItemOverride_GetItem
    pop {r0-r12, lr}
    bx lr


.global hook_CheckCurrentInventory
hook_CheckCurrentInventory:
    push {r1-r12, lr}
    bl ItemOverride_CheckInventoryItemOverride
    pop {r1-r12, lr}
    b 0x1F3D6C

.global hook_OverrideItemIdIndex
hook_OverrideItemIdIndex:
    push {r0}
    ldr r0,.rActiveItemGraphicId_addr
    ldr r0,[r0]
    cmp r0,#0x0
    pop {r0}
    beq noOverrideItemIdIndex
    ldr r0,.rActiveItemGraphicId_addr
    ldr r0,[r0]
    bx lr
noOverrideItemIdIndex:
    ldrsh r0, [r0, #-6]
    bx lr

.global hook_OverrideDrawIndex
hook_OverrideDrawIndex:
    ldr r0,.rActiveItemGraphicId_addr
    ldr r0,[r0]
    cmp r0,#0x0
    beq noOverrideGraphicId
    b 0x22F254
noOverrideGraphicId:
    ldrsh r0,[r7,#0x2]
    b 0x22F250

.global hook_OverrideDrawIndexSecond
hook_OverrideDrawIndexSecond:
    ldr r0,.rActiveItemGraphicId_addr
    ldr r0,[r0]
    cmp r0,#0x0
    beq noOverrideGraphicIdSecond
    b 0x22F47C
noOverrideGraphicIdSecond:
    ldrsh r0, [r8,#2]
    b 0x22F478

.global hook_OverrideTextID
hook_OverrideTextID:
    push {r3}
    ldr r3,.rActiveItemTextId_addr
    ldr r3,[r3]
    cmp r3,#0x0
    pop {r3}
    beq noOverrideTextID
    b 0x231104
noOverrideTextID:
    @cpy r2, r5
    cpy r0, r7
    b 0x231100

.global hook_OverrideItemID 
hook_OverrideItemID:
    push {r1}
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    pop {r1}
    beq noOverrideItemID
    push {r0-r12, lr}
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    b 0x231110
noOverrideItemID:
    LDRB R1, [R4,#0x0]
    cpy r0,r7
    b 0x23110C



.global hook_DarmaniRewardCheck
hook_DarmaniRewardCheck:
    push {r0-r12, lr}
    bl ItemOverride_CheckDarmaniGivenItem
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq doNotSpawnDarmani
    b 0x2DE794
doNotSpawnDarmani:
    nop
    b 0x2DE96C

.global hook_CheckOshExtData
hook_CheckOshExtData:
    push {lr}
    bl ItemOverride_GetOshExtData
    pop {lr}
    cmp r0,#0x0
    bx lr

.global hook_GoronMaskGiveItem
hook_GoronMaskGiveItem:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x79
    bl ItemOverride_GetSoHItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideDarmaniItemID
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    cpy r0,r5
    b 0x41DAB4
noOverrideDarmaniItemID:
    cpy r0,r5
    bl 0x233BEC
    b 0x41DAB4

.global hook_ZoraMaskGiveItem
hook_ZoraMaskGiveItem:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x7A
    bl ItemOverride_GetSoHItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideMikauItemID
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    cpy r0,r5
    b 0x41DB84
noOverrideMikauItemID:
    cpy r0,r5
    bl 0x233BEC
    b 0x41DB84

.global hook_GibdoMaskGiveItem
hook_GibdoMaskGiveItem:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x87
    bl ItemOverride_GetSoHItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideGibdoItemID
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    cpy r0,r5
    b 0x41DC4C
noOverrideGibdoItemID:
    cpy r0,r5
    bl 0x233BEC
    b 0x41DC4C

.global hook_CouplesMaskGiveItem
hook_CouplesMaskGiveItem:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    mov r2,#0x85
    bl ItemOverride_GetSoHItem
    ldr r5,.rActiveItemRow_addr
    ldr r5,[r5]
    cmp r5,#0x0
    pop {r0-r12, lr}
    beq noOverrideCouplesItemID
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r4
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    b 0x46e264
noOverrideCouplesItemID:
    b 0x46e22c

.global hook_AdjustCouplesMaskMessage
hook_AdjustCouplesMaskMessage:
    push {r1}
    ldr r1,.rStoredTextId_addr
    ldr r1,[r1]
    cmp r1,#0x0
    pop {r1}
    beq normalText
    ldr r1,.rStoredTextId_addr
    ldr r1,[r1]
    push {r0-r12,lr}
    bl ItemOverride_RemoveTextId
    pop {r0-r12, lr}
    b 0x1867C8
normalText:
    mov r1,#0xA2
    b 0x1867C8

.global hook_ChangeSOHToCustomText
hook_ChangeSOHToCustomText:
    push {r0-r2, lr}
    bl ItemOverride_SwapSoHGetItemText
    pop {r0-r2, lr}
    b 0x186814