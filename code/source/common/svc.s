.global svcOutputDebugString
.type svcOutputDebugString, %function
svcOutputDebugString:
   str r0, [sp,#-0x4]!
   svc 0x3D
   ldr r2, [sp], #4
   str r1, [r2]
   bx lr

.global svcSleepThread
.type svcSleepThread, %function
svcSleepThread:
    svc 0x0A
    bx lr

.global svcFlushProcessDataCache
.type svcFlushProcessDataCache, %function
svcFlushProcessDataCache:
	svc 0x54
	bx  lr

.global svcCloseHandle
.type svcCloseHandle, %function
svcCloseHandle:
	svc 0x23
	bx  lr

.global svcWaitSynchronization
.type svcWaitSynchronization, %function
svcWaitSynchronization:
	svc 0x24
	bx  lr

.global svcCreateThread
.type svcCreateThread, %function
svcCreateThread:
	push {r0, r4}
	ldr  r0, [sp, #0x8]
	ldr  r4, [sp, #0x8+0x4]
	svc  0x08
	ldr  r2, [sp], #4
	str  r1, [r2]
	ldr  r4, [sp], #4
	bx   lr

.global svcExitThread
.type svcExitThread, %function
svcExitThread:
	svc 0x09
	bx  lr

.global svcArbitrateAddress
.type svcArbitrateAddress, %function
svcArbitrateAddress:
	push {r4, r5}
	ldr r4, [sp, #8]
	ldr r5, [sp, #12]
	svc 0x22
	pop {r4, r5}
	bx  lr

.global svcQueryMemory
.type svcQueryMemory, %function
svcQueryMemory:
	push {r0, r1, r4-r6}
	svc  0x02
	ldr  r6, [sp]
	str  r1, [r6]
	str  r2, [r6, #4]
	str  r3, [r6, #8]
	str  r4, [r6, #0xc]
	ldr  r6, [sp, #4]
	str  r5, [r6]
	add  sp, sp, #8
	pop  {r4-r6}
	bx   lr
