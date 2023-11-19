@ This file has been taken and modified from
@ https://github.com/leoetlino/project-restoration/blob/181ecbf6e806fc10c8d1f8b2d74489b0bd7f5e67/hooks/rst_zora_swim.hks
.arm
.text
.syntax unified

.global hook_ZoraInWaterFastSwim
hook_ZoraInWaterFastSwim:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  beq useDefaultBehaviour
  bl SwitchToZoraFastSwim
  b 0x1F0C7C
useDefaultBehaviour:
  bl 0x220EA0
  b 0x1F0C7C

.global hook_FifthZoraSwimCheck
hook_FifthZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne doFifthFastSwim
  ldr r1,[r10,#0x9cc]
  b 0x1FFA88
doFifthFastSwim:
  bl ShouldUseZoraFastSwim
  cmp r0,#1
  b 0x1FFA94
  
@ This is causing some UB with holding R.
@ Regular game allows us to hold R and will stop
@ boost movement where this enables it to go continuously.
.global hook_UseZoraASwimSecond
hook_UseZoraASwimSecond:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  beq fastSwimDisabled
  blne ShouldUseZoraFastSwim
  cmp r0,#1
  b 0x1FFD84
fastSwimDisabled:
  ldr r1,[r10,#0x9cc]
  b 0x1FFD78

@ This is the animation to do with the startup flip.
.global hook_ThirdZoraSwimCheck
hook_ThirdZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne doThirdFastSwim
  cmp r0,#0x0
  bx lr
doThirdFastSwim:
  bl runZoraPatch 
  b 0x1FFDC0

.global hook_CheckMagicForZoraFastSwim
hook_CheckMagicForZoraFastSwim:
  beq 0x200010
  push {r0}
  bl CheckIfMagicAcquired
  cmp r0, #0x0
  pop {r0}
  beq 0x200010
  @cmp r0,#0x0
  b 0x1FFDEC

.global hook_ZoraBarrierCheckMagicAcquired
hook_ZoraBarrierCheckMagicAcquired:
  beq 0x2072B4
  push {r0}
  bl CheckIfMagicAcquired
  cmp r0, #0x0
  pop {r0}
  beq 0x2072B4
  cmp r1, #0x0
  b 0x207234

.global hook_ChangeTriggerAandRToA
hook_ChangeTriggerAandRToA:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  beq triggerIsDefault
  bl ShouldUseZoraFastSwim
  cmp r0, #0x0
  b 0x220F2C
triggerIsDefault:
  cmp r2,#0x0
  ldr r0, [r0, r4]
  b 0x220F00

.global hook_FourthZoraSwimCheck
hook_FourthZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne doFourthFastSwim
  ldr r0, [r0, #8]
  b 0x220F30
doFourthFastSwim:
  cmp r0, #1
  @ Basically calling a nop for 0x220F30
  b 0x220F34

.global hook_FirstZoraSwimCheck
hook_FirstZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne doFirstFastSwim
  cmp r2,#0x0
  mov r0,#0x1
  b 0x220F64
doFirstFastSwim:
  bl runZoraPatch
  b 0x220F64

.global hook_SecondZoraSwimCheck
hook_SecondZoraSwimCheck:
  push {r0-r12, lr}
  bl SettingsEnabledFastSwim
  cmp r0, #0x0
  pop {r0-r12, lr}
  bne doSecondFastSwim
  ldrb r0, [r10, #0x3F]
  b 0x2210E0
doSecondFastSwim:
  bl runZoraPatch
  b 0x2210E0

runZoraPatch:
  smlatteq r0, r3, r0, sl
  bx lr

runZoraASwim:
  bl ShouldUseZoraFastSwim
  bx lr