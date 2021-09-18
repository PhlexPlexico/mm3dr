.arm

.section .patch_DecoupleZlZr
.global patch_DecoupleZlZr
patch_DecoupleZlZr:
    b 0x50

@.section .patch_MainLoop
@.global patch_MainLoop
@patch_MainLoop:
@    bl hook_MainLoop

.section .patch_DecoupleStartSelect
.global patch_DecoupleStartSelect
patch_DecoupleStartSelect:
    mov r0, #1
    ldrsb R0, [R0]
    bx lr

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
    
.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader
