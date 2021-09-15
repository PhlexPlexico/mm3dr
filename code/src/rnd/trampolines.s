.section ".init"
.align 4

.macro TRAMPOLINE_DECLARE name
	.global rst_trampoline_\name
	.type rst_trampoline_\name, %function
	.align 4
rst_trampoline_\name:
.endm

.macro TRAMPOLINE_R0_RESULT name
	TRAMPOLINE_DECLARE \name
  push {r1-r12, lr}
  vpush {d0-d15}
  bl \name
  vpop {d0-d15}
  pop {r1-r12, pc}
.endm

.macro TRAMPOLINE_CMP_RESULT name, val
  TRAMPOLINE_DECLARE \name
  push {r0-r12, lr}
  vpush {d0-d15}
  bl \name
  cmp r0, \val
  vpop {d0-d15}
  pop {r0-r12, pc}
.endm

.global rst_dummy
rst_dummy:
  nop

TRAMPOLINE_DECLARE rst_HandleOcarinaSong
  push {lr}

  push {r0-r12}
  vpush {d0-d15}
  mov r1, r0 // song
  mov r0, r4 // MessageWindow* this
  bl rst_HandleOcarinaSong
  cmp r0, #0
  vpop {d0-d15}
  pop {r0-r12}

  // jump out of this trampoline and MessageWindow code directly
  addne sp, sp, #0x70
  popne {r4-r11, pc}

  cmp r0, #0x16 // original instruction
  pop {pc}


TRAMPOLINE_DECLARE rst_GameStateGetNextStateInfo
  push {r1-r7, r9-r12, lr}
  mov r0, r6  // this
  bl rst_GameStateGetNextStateInfo
  mov r8, r0 // state
  mov r0, r6 // original instruction
  pop {r1-r7, r9-r12, pc}
