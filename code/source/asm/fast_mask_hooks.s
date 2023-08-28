.arm
.text

.global hook_DoNotForceMaskChange
hook_DoNotForceMaskChange:
  push {r0-r12, lr}
  bl SettingsFastMaskCheck
  cmp r0,#0x0
  pop {r0-r12, lr}
  beq defaultForceMaskChange
  @ act as nop for the strbne.
  b 0x1DB320
defaultForceMaskChange:
  push {r0-r12, lr}
  bl ZoraMaskCheck
  cmp r0, #0xFF
  pop {r0-r12,lr}
  b 0x1DB318


.global hook_HandleFastMaskTransforms
hook_HandleFastMaskTransforms:
  push {r0-r12, lr}
  bl SettingsFastMaskCheck
  cmp r0,#0x0
  pop {r0-r12, lr}
  beq defaultMaskTransform
  push {r0-r12, lr}
  bl HandleFastTransform
  pop {r0-r12, lr}
  mov r5,#0x0
  bx lr
defaultMaskTransform:
  mov r5, #0x0
  b 0x1DB748

.global hook_BypassMaskEquipmentChecks
hook_BypassMaskEquipmentChecks:
  push {r0-r12, lr}
  bl SettingsFastMaskCheck
  cmp r0,#0x0
  pop {r0-r12, lr}
  beq defaultDoNotBypassCheck
  b 0x1E7768
defaultDoNotBypassCheck:
  b 0x1E7718

.global hook_BypassFirstPersonModeChecks
hook_BypassFirstPersonModeChecks:
  push {r0-r12, lr}
  bl SettingsFastMaskCheck
  cmp r0,#0x0
  pop {r0-r12, lr}
  beq defaultDoNotBypassEquipmentCheck
  b 0x1EE0A8
defaultDoNotBypassEquipmentCheck:
  ldrb lr, [r4,#0x20b]
  cmp lr, #0x0 
  beq 0x1EE0A8
  b 0x1EDFB8

.global hook_RemoveGoronRollChecksWithoutMask
hook_RemoveGoronRollChecksWithoutMask:
  push {r0-r12, lr}
  bl SettingsFastMaskCheck
  cmp r0,#0x0
  pop {r0-r12, lr}
  beq defaultDoNotIgnoreGoronCheck
  b 0x1F7A1C
defaultDoNotIgnoreGoronCheck:
  b 0x1F78D8