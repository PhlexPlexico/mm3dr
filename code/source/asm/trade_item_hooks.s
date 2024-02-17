.arm
.text

.global hook_RemoveTradeItemFromInventory
hook_RemoveTradeItemFromInventory:
  push {r0-r12,lr}
  cpy r0,r2
  mov r1,#0x5
  sub r0,r0,#0x1
  bl SaveFile_RemoveStoredTradeItem
  pop {r0-r12,lr}
  beq 0x477748
  bx lr

.global hook_RemoveMoonTearFromInventory
hook_RemoveMoonTearFromInventory:
  push {r0-r12,lr}
  mov r2, #0x97
  cpy r0,r2
  mov r1,#0x5
  sub r0,r0,#0x1
  bl SaveFile_RemoveStoredTradeItem
  pop {r0-r12,lr}
  cpy r5,r1
  bx lr

.global hook_RemoveTradeItemFromExtSlot
hook_RemoveTradeItemFromExtSlot:
  push {r0-r12, lr}
  bl SaveFile_RemoveTradeItemFromSlot 
  pop {r0-r12, lr}
  cpy r2,r1
  bx lr

.global hook_RemoveKafeiItemFromExtSlot
hook_RemoveKafeiItemFromExtSlot:
  push {r0-r12, lr}
  bl SaveFile_GetItemCurrentlyInSlot
  cmp r0,#0x2F
  beq changeLetter
  cmp r0,#0x30
  beq changePendant
  pop {r0-r12, lr}
  cpy r5,r0
  bx lr
changeLetter:
  mov r0,#0xAA
  mov r1,#0x11
  bl SaveFile_RemoveStoredTradeItem
  pop {r0-r12,lr}
  b 0x4AD1C4
changePendant:
  mov r0,#0xAB
  mov r1,#0x11
  bl SaveFile_RemoveStoredTradeItem
  pop {r0-r12,lr}
  b 0x4AD1C4
  

.global hook_SwapStoredTradeItems
hook_SwapStoredTradeItems:
  push {r0-r12, lr}
  bl GearScreen_GetStoredTradeItem
  pop {r0-r12, lr}
  cpy r4, r0
  bx lr