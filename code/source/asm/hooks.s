.arm
.text

.global rCustomDungeonItemRetrieved
.rCustomDungeonItemRetrieved_addr:
    .word rCustomDungeonItemRetrieved

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

.global hook_Gfx_Update
hook_Gfx_Update:
    push {r0-r12, lr}
    bl Gfx_Update
    pop {r0-r12, lr}
    pop {r4-r8, pc}

.global hook_Gfx_AwakeCallback
hook_Gfx_AwakeCallback:
    push {r0-r12, lr}
    bl Gfx_AwakeCallback
    pop {r0-r12, lr}
    add r0,r0,#0xC
    b 0x124DEC

.global hook_Gfx_SleepQueryCallback
hook_Gfx_SleepQueryCallback:
    push {r0-r12, lr}
    bl Gfx_SleepQueryCallback
    pop {r0-r12, lr}
    add r0,r0,#0xC
    b 0x124DF4

.global hook_OverrideCutsceneNextEntrance
hook_OverrideCutsceneNextEntrance:
    push {r0-r12, lr}
    bl SceneEntranceOverride
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne doNotOverrideCutscene
    bx lr
doNotOverrideCutscene:
    bl 0x22A7F8
    b 0x1B1838

.global hook_DoNotResetTempleFlags
hook_DoNotResetTempleFlags:
    push {r0-r12, lr}
    bl ForceTempleFlags
    pop {r0-r12, lr}
    mov r0,#0x0
    bx lr

.global hook_SpawnFastElegyStatues
hook_SpawnFastElegyStatues:
    push {r0-r12, lr}
    bl PlayerStateSpawningElegyStatue
    cmp r0, #0x0
    pop {r0-r12, lr}
    cpy r2, r1
    beq 0x1E9FBC
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

.global hook_CheckDungeonItems
hook_CheckDungeonItems:
    push {r0-r12, lr}
    ldr r1,.rCustomDungeonItemRetrieved_addr
    ldr r1,[r1]
    cmp r1,#0x1
    pop {r0-r12, lr}
    beq 0x233F64
    ldrh r2, [r2, #82]
    bx lr

.global hook_CheckDungeonSmallKeys
hook_CheckDungeonSmallKeys:
    push {r0-r12, lr}
    ldr r1,.rCustomDungeonItemRetrieved_addr
    ldr r1,[r1]
    cmp r1,#0x1
    pop {r0-r12, lr}
    beq 0x233F64
    ldrh r0, [r2, #0x52]
    bx lr

.global hook_BlastMaskCooldown
hook_BlastMaskCooldown:
    push {r0-r12, lr}
    bl checkBlastMaskCooldown
    cmp r0,#0x0
    beq defaultBlastCd
    cmp r0,#0x1
    beq shortBlastCd
    cmp r0,#0x2
    beq veryShortBlastCd
    cmp r0,#0x3
    beq instBlastCd
defaultBlastCd:
    pop {r0-r12, lr}
    cmp r0,#0x0
    subne r0,r0,#0x1
    bx lr
shortBlastCd:
    pop {r0-r12, lr}
    cmp r0,#0x0
    subne r0,r0,#0x2
    bx lr
veryShortBlastCd:
    pop {r0-r12, lr}
    cmp r0,#0x0
    subne r0,r0,#0x5
    bx lr
instBlastCd:
    pop {r0-r12, lr}
    cmp r0,#0x0
    subne r0,r0,r0
    bx lr

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

.global hook_OverrideBomberTextID
hook_OverrideBomberTextID:
    cmp r1, #0x5F
    beq noBomberOverride
    cmp r0,r0
    b 0x1D2768
noBomberOverride:
    cmp r1,r0
    b 0x1D2768

.global hook_EnteringLocation
hook_EnteringLocation:
    push {r0-r12, lr}
    bl Entrance_EnteredLocation
    pop {r0-r12, lr}
    cpy r9,r0
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

.global hook_checkChestContentSetting
hook_checkChestContentSetting:
    push {r0-r12, lr}
    cpy r0,r4
    ldrb r1,[r4,#0x3E9]
    bl Chest_IsOverrideEnabled
    cmp r0,#0x0
    beq drawFancyMapChests
    pop {r0-r12,lr}
    bx lr
drawFancyMapChests:
    pop {r0-r12,lr}
    cmpne r0,#0x3C
    bx lr

.global hook_changeChestTypeToMatchContents
hook_changeChestTypeToMatchContents:
    push {r0-r3, r5-r12, lr}
    cpy r0, r4
    cpy r1, r5
    bl Chest_OverrideSize
    cmp r0,#0xFF
    beq doNotOverrideChestType
    strb r0,[r4,#0x3e9]
    pop {r0-r3, r5-r12, lr}
    strh r7, [r4,#0x18]
    bx lr
doNotOverrideChestType:
    pop {r0-r3, r5-r12, lr}
    strh r7, [r4,#0x18]
    bx lr

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

.global hook_CheckMoTSetting
hook_CheckMoTSetting:
    bl SettingsMaskOfTruthCheck
    b 0x35C42C

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100024
    b  0x100004
