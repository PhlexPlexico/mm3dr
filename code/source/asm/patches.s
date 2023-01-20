.arm

.section .patch_DecoupleZlZr
.global patch_DecoupleZlZr
patch_DecoupleZlZr:
    b 0x0116718

.section .patch_SpawnFastElegyStatues
.global patch_SpawnFastElegyStatues
patch_SpawnFastElegyStatues: 
    b hook_SpawnFastElegyStatues

.section .patch_startHeap
.global patch_startHeap
patch_startHeap:
    bl hook_Start

.section .patch_FixSurroundSound
.global patch_FixSurroundSound
patch_FixSurroundSound:
    nop
    nop
    nop
    nop
    nop

.section .patch_OcarinaDive
.global patch_OcarinaDive
patch_OcarinaDive:
    bl hook_CheckOcarinaDive

.section .patch_IncomingGetItemID
.global IncomingGetItemID_patch
IncomingGetItemID_patch:
    bl hook_IncomingGetItemID

.section .patch_MainLoop
.global patch_MainLoop
patch_MainLoop:
    b hook_MainLoop

.section .patch_DecoupleStartSelect
.global patch_DecoupleStartSelect
patch_DecoupleStartSelect:
    nop

@ Skip past all chest content resetting.
@ Since this is rando, we don't want users
@ getting chests again, and instead of
@ keeping track via extdata we can just 
@ branch over everything in relation to 
@ resetting all the chests in the game.
.section .patch_AttemptKeepChestsClosed
.global patch_AttemptKeepChestsClosed
patch_AttemptKeepChestsClosed:
    b 0x01c936c

@ Skips past a loop that resets all
@ values in the each dungeon for 
@ keys/fairies/boss key/etc
@ to zero. Small QoL if boss
@ keys are already given, same with keys
.section .patch_DoNotRemoveKeys
.global patch_DoNotRemoveKeys
patch_DoNotRemoveKeys:
    nop
    nop
    nop
    nop
    nop
    nop
    nop

.section .patch_DisableMilkTimer
.global patch_DisableMilkTimer
patch_DisableMilkTimer:
    nop

.section .patch_LoadExtData
.global patch_LoadExtData
patch_LoadExtData:
    bl hook_SaveFile_Load

.section .patch_SaveFile_init
.global patch_SaveFile_init
patch_SaveFile_init:
    bl hook_SaveFile_Init

.section .patch_GetCustomText
.global patch_GetCustomText
patch_GetCustomText:
    b GetMessageFromId

.section .patch_ISGCrouchStabOne
.global patch_ISGCrouchStabOne
patch_ISGCrouchStabOne:
    nop
    nop
    nop


.section .patch_ISGCrouchStabTwo
.global patch_ISGCrouchStabTwo
patch_ISGCrouchStabTwo:
    nop
    nop
    nop

.section .patch_RemoveRemainsStateCheck
.global patch_RemoveRemainsStateCheck
patch_RemoveRemainsStateCheck:
    b hook_RemainsCheckValue

.section .patch_ChangeDrawItemIndex
.global OverrideDrawIndex_patch
OverrideDrawIndex_patch:
    b hook_OverrideDrawIndex

.section .patch_ChangeDrawItemIndexSecond
.global patch_ChangeDrawItemIndexSecond
patch_ChangeDrawItemIndexSecond:
    b hook_OverrideDrawIndexSecond

.section .patch_OverrideTextID
.global OverrideTextID_patch
OverrideTextID_patch:
    b hook_OverrideTextID

.section .patch_OverrideBomberTextID
.global OverrideBomberTextID_patch
OverrideBomberTextID_patch:
    b hook_OverrideBomberTextID

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    b hook_OverrideItemID

.section .patch_OverrideFairyGiveItem
.global OverrideFairyItemID_patch
OverrideFairyItemID_patch:
    b hook_OverrideFairyItem


.section .patch_OverrideGreatFairySpawn
.global OverrideGreatFairySpawn_patch
OverrideGreatFairySpawn_patch:
    nop
    @ldmia sp!,{r4 - r6, pc}
    @ldmia sp !, {r4 - r6, lr}
    @ bx lr

.section .patch_ReadGamePad
.global patch_ReadGamePad
patch_ReadGamePad:
    b hook_readGamePad

.section .patch_DisableExistingTrigger
.global patch_DisableExistingTrigger
patch_DisableExistingTrigger:
    b 0x059bb60 @branches past all the checks for button presses and whatnot. We override all of this.

.section .patch_ItemCloseOnSelect
.global patch_ItemCloseOnSelect
patch_ItemCloseOnSelect:
    tst r1, #14

@ Adjusts ocarina songs to be in-line with restoration
.section .patch_HandleOcarinaHooks
.global patch_HandleOcarinaHooks
patch_HandleOcarinaHooks:
    b hook_HandleOcarina

@ Remove call from twinmold->life -= twinmold_min_damage.
.section .patch_TwinmoldConsistentDamage
.global patch_TwinmoldConsistentDamage
patch_TwinmoldConsistentDamage:
    nop

.section .patch_FasterBlockMovement
.global patch_FasterBlockMovement
patch_FasterBlockMovement:
    .float 50.0

.section .patch_FasterBlockMovementBack
.global patch_FasterBlockMovementBack
patch_FasterBlockMovementBack:
    .float 60.0

.section .patch_SaveExtDataOnOwl
.global patch_SaveExtDataOnOwl
patch_SaveExtDataOnOwl:
    b hook_OwlExtDataSave

.section .patch_AromaItemCheck
.global patch_AromaItemCheck
patch_AromaItemCheck:
    b hook_AromaItemCheck

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader
