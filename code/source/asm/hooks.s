.arm
.text

.global rActiveItemTextId
.rActiveItemTextId_addr:
    .word rActiveItemTextId

.global hook_Start
hook_Start:
    push {r0-r12, lr}
    bl _start
    pop {r0-r12, lr}
    b 0x0103EC8

.global hook_MainLoop
hook_MainLoop:
    push {r0-r12, lr}
    bl calc
    pop {r0-r12, lr}
    ldr r1, [r0,#0x138]
    b 0x0106770

.global hook_ChangeSOHToCustomText
hook_ChangeSOHToCustomText:
    push {r0-r2, lr}
    bl ItemOverride_SwapSoHGetItemText
    pop {r0-r2, lr}
    b 0x186814

.global hook_SpawnFastElegyStatues
hook_SpawnFastElegyStatues:
    push {r0-r12, lr}
    bl PlayerStateSpawningElegyStatue
    cmp r0, #0x0
    pop {r0-r12, lr}
    cpy r2, r1
    beq 0x1E9FBC
    bx lr

.global hook_CheckCurrentInventory
hook_CheckCurrentInventory:
    push {r1, lr}
    bl ItemOverride_CheckInventoryItemOverride
    cmp r0,#0xFF
    pop {r1, lr}
    bne DoNotOverrideInventoryCheck
    bx lr
DoNotOverrideInventoryCheck:
    bx lr

.global hook_CheckOcarinaDive
hook_CheckOcarinaDive:
    push {r0-r12, lr}
    bl SettingsEnableOcarinaDive
    cmp r0, #0x0
    pop {r0-r12, lr}
    bne 0x1e1f10
    tst r0,#0x1
    beq 0x1E1FB4
    b 0x1e1f10

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global rActiveItemGraphicId
.rActiveItemGraphicId:
    .word rActiveItemGraphicId

.global rStoredBomberNoteTextId
.rStoredBomberNoteTextId:
    .word rStoredBomberNoteTextId

.global hook_SaveFile_Load
hook_SaveFile_Load:
    push {r0-r12, lr}
    bl SaveFile_LoadExtSaveData
    pop {r0-r12, lr}
    str r5,[r1,#0x61C]
    b 0x48C764

.global hook_SaveFile_Init
hook_SaveFile_Init:
    push {r0-r12, lr}
    cpy r0,r4
    bl SaveFile_Init
    pop {r0-r12, lr}
    mov r3,#0x0
    b 0x5b8b28  

@ State handler calls 0x5D for masks, check this value and ignore states where that is equal, since this function
@ is also used by song of soaring and get_item.
.global hook_RemainsCheckValue
hook_RemainsCheckValue:
    cmp r7,#0x5D
    beq noIgnoreValues
    cpy r1,r4
    b 0x22B7C0
noIgnoreValues:
    b 0x22B814

.global hook_OverrideDrawIndex
hook_OverrideDrawIndex:
    ldr r0,.rActiveItemGraphicId
    ldr r0,[r0]
    cmp r0,#0x0
    beq noOverrideGraphicId
    b 0x22F254
noOverrideGraphicId:
    ldrsh r0,[r7,#0x2]
    b 0x22F250

.global hook_OverrideDrawIndexSecond
hook_OverrideDrawIndexSecond:
    ldr r0,.rActiveItemGraphicId
    ldr r0,[r0]
    cmp r0,#0x0
    beq noOverrideGraphicIdThird
    b 0x22F47C
noOverrideGraphicIdThird:
    ldrsh r0, [r8,#2]
    b 0x22F478

.global hook_OverrideTextID
hook_OverrideTextID:
    push {r3}
    ldr r3,.rActiveItemRow_addr
    ldr r3,[r3]
    cmp r3,#0x0
    pop {r3}
    beq noOverrideTextID
    b 0x231104
noOverrideTextID:
    @cpy r2, r5
    cpy r0, r7
    b 0x231100


.global hook_OverrideBomberTextID
hook_OverrideBomberTextID:
    push {r0}
    sub r0,#0x600
    cmp r0,#0x18
    pop {r0}
    beq noOverrideBomberTextID
    push {r1}
    ldr r1,.rStoredBomberNoteTextId
    ldr r1,[r1]
    cmp r1,#0x0
    pop {r1}
    beq noOverrideBomberTextID
    bl ItemOverride_RemoveTextId
    b 0x1D2768
noOverrideBomberTextID:
    cmp r0,r0
    b 0x1D2768

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

.global hook_readGamePad
hook_readGamePad:
    push {r0-r12, lr}
    bl readPadInput
    pop {r0-r12, lr}
    tst r0,r1
    b 0x59ba14

.global hook_HandleOcarina
hook_HandleOcarina:
    push {r0-r12, lr}
    mov r1, r0 @ song
    mov r0, r4 @ MessageWindow* this
    bl HandleOcarinaSong
    cmp r0, #0
    pop {r0-r12, lr}
    bne 0x606424
    cmp r0, #0x16 @ original instruction
    b 0x604d90

.global hook_OwlExtDataSave
hook_OwlExtDataSave:
    push {r0-r12, lr}
    bl SaveFile_SaveExtSaveData
    pop {r0-r12, lr}
    cpy r6,r0
    b 0x317008

.global hook_MikauRewardCheck
hook_MikauRewardCheck:
    push {r0-r12, lr}
    bl ItemOverride_CheckMikauGivenItem
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq doNotSpawnMikau
    b 0x32BC20
doNotSpawnMikau:
    nop
    b 0x32BBDC

.global hook_AromaItemCheck
hook_AromaItemCheck:
    push {r0-r12, lr}
    bl ItemOverride_CheckAromaGivenItem
    cmp r0,#0x1
    pop {r0-r12, lr}
    b 0x350920

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
    mov r2,#0x7A
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

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100024
    b  0x100004
