.arm

.section .patch_PostActorCalc
.global patch_PostActorCalc
patch_PostActorCalc:
  bl hook_PostActorCalc