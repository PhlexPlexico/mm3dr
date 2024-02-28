.arm
.text

.global hook_PostActorCalc
hook_PostActorCalc:
  push {r0-r12, lr}
  bl PostActorCalc @ found in main.cpp
  pop {r0-r12,lr}
  add r3,r5,#0x10
  bx lr