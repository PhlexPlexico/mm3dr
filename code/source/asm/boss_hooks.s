.arm
.text

.global hook_PostActorCalc
hook_PostActorCalc:
  push {r0-r12, lr}
  bl PostActorCalc @ found in main.cpp
  pop {r0-r12,lr}
  add r3,r5,#0x10
  bx lr

.global hook_TwinmoldConsistentDamage
hook_TwinmoldConsistentDamage:
  push {r0-r12, lr}
  bl IsTwinmoldSetToRestoration
  cmp r0,#0x1
  beq restorationTwinmold
  pop {r0-r12,lr}
  sub r0,r2,r0
  bx lr
restorationTwinmold:
  pop {r0-r12,lr}
  bx lr