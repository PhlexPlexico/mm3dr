@ This file has been taken and modified from
@ https://github.com/leoetlino/project-restoration/blob/181ecbf6e806fc10c8d1f8b2d74489b0bd7f5e67/hooks/rst_zora_swim.hks
.arm
.text

.global hook_UseZoraASwimSecond
hook_UseZoraASwimSecond:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  blne ShouldUseZoraFastSwim
  pop {r0-r12, lr}
  cmpeq r0,#0x0
  ldr r1,[r10,#0x9cc]
  b 0x1FFD78

.global hook_ThirdZoraSwimCheck
hook_ThirdZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne runZoraPatch 
  cmp r0,#0x0
  b 0x1FFDC0

.global hook_UseZoraASwimFirst
hook_UseZoraASwimFirst:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  blne ShouldUseZoraFastSwim
  pop {r0-r12, lr}
  cmp r2,#0x0
  ldr r0,[r0,r4]
  b 0x220F00
  
.global hook_FirstZoraSwimCheck
hook_FirstZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne runZoraPatch
  cmp r2,#0x0
  mov r0,#0x1
  b 0x220F64

.global hook_SecondZoraSwimCheck
hook_SecondZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne runZoraPatch
  b 0x2210E4

runZoraPatch:
  smlatteq r0, r3, r0, sl
  bx lr

runZoraASwim:
  bl ShouldUseZoraFastSwim
  bx lr