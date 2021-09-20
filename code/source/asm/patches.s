.arm

.section .patch_DecoupleZlZr
.global patch_DecoupleZlZr
patch_DecoupleZlZr:
    b 0x0116718

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

.section .patch_fasterBlockMovement
.global patch_fasterBlockMovement
patch_fasterBlockMovement:
    .float 50.0

.section .patch_fasterBlockMovementBack
.global patch_fasterBlockMovementBack
patch_fasterBlockMovementBack:
    .float 60.0

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader
