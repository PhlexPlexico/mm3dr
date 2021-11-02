.arm

.section .patch_DecoupleZlZr
.global patch_DecoupleZlZr
patch_DecoupleZlZr:
    b 0x0116718

@ .section .patch_startHeap
@ .global patch_startHeap
@ patch_startHeap:
@     STMFD SP!, {R4-R8,LR}
@     b hook_Start

.section .patch_FixSurroundSound
.global patch_FixSurroundSound
patch_FixSurroundSound:
    nop
    nop
    nop
    nop
    nop

.section .patch_IncomingGetItemID
.global IncomingGetItemID_patch
IncomingGetItemID_patch:
    str r6, [r5,#0x920]
    bl hook_IncomingGetItemID

.section .patch_MainLoop
.global patch_MainLoop
patch_MainLoop:
    b hook_MainLoop

.section .patch_DecoupleStartSelect
.global patch_DecoupleStartSelect
patch_DecoupleStartSelect:
    nop

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

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    b hook_OverrideItemID

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

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader
