.arm

.section .patch_DoNotForceMaskChange
.global patch_DoNotForceMaskChange
patch_DoNotForceMaskChange:
    bl hook_DoNotForceMaskChange

.section .patch_HandleFastMaskTransforms
.global patch_HandleFastMaskTransforms
patch_HandleFastMaskTransforms:
    bl hook_HandleFastMaskTransforms

.section .patch_BypassMaskEquipmentChecks
.global patch_BypassMaskEquipmentChecks
patch_BypassMaskEquipmentChecks:
    bl hook_BypassMaskEquipmentChecks

@ This just allows us to use X and Y to speed
@ up the mask buttons. Makes it easier for mashing.
@ We don't need an option for this.
.section .patch_FastTransformCutsceneSkipBtns
.global patch_FastTransformCutsceneSkipBtns
patch_FastTransformCutsceneSkipBtns:
    .word 0xCF3

.section .patch_BypassFirstPersonModeChecks
.global patch_BypassFirstPersonModeChecks
patch_BypassFirstPersonModeChecks:
    bl hook_BypassFirstPersonModeChecks

.section .patch_RemoveGoronRollChecksWithoutMask
.global patch_RemoveGoronRollChecksWithoutMask
patch_RemoveGoronRollChecksWithoutMask:
    bl hook_RemoveGoronRollChecksWithoutMask