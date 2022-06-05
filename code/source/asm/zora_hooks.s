.arm
.text

.global hook_ThirdZoraSwimCheck
hook_ThirdZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne runZoraPatch
  cmp r0,#0x0
  b 0x1FFDC0


.global hook_FirstZoraSwimCheck
hook_FirstZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne runZoraPatch
  mov r0,#0x1
  b 0x220F64

.global hook_SecondZoraSwimCheck
hook_SecondZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne runZoraPatch
  mov r0,#0x1
  b 0x2210E0

runZoraPatch:
  smlatteq r0, r3, r0, sl
  bx lr