.arm

.section .patch_ISGCrouchStabOne
.global patch_ISGCrouchStabOne
patch_ISGCrouchStabOne:
    b 0xc

.section .patch_ISGCrouchStabTwo
.global patch_ISGCrouchStabTwo
patch_ISGCrouchStabTwo:
    b 0xc

.section .patch_loader
.global loader_patch

loader_patch:
    b hook_into_loader