.arm

.section .patch_TingleCheckClocktownMap
.global patch_TingleCheckClocktownMap
patch_TingleCheckClocktownMap:
    mov r0,#0x1
    bl hook_CheckTingle

.section .patch_TingleCheckWoodfallMap
.global patch_TingleCheckWoodfallMap
patch_TingleCheckWoodfallMap:
    mov r0,#0x2
    bl hook_CheckTingle

.section .patch_TingleCheckSnowheadMap
.global patch_TingleCheckSnowheadMap
patch_TingleCheckSnowheadMap:
    mov r0,#0x4
    bl hook_CheckTingle

.section .patch_TingleCheckRomaniMap
.global patch_TingleCheckRomaniMap
patch_TingleCheckRomaniMap:
    mov r0,#0x8
    bl hook_CheckTingle

.section .patch_TingleCheckGreatBayMap
.global patch_TingleCheckGreatBayMap
patch_TingleCheckGreatBayMap:
    mov r0,#0x10
    bl hook_CheckTingle

.section .patch_TingleCheckStoneTowerMap
.global patch_TingleCheckStoneTowerMap
patch_TingleCheckStoneTowerMap:
    mov r0,#0x20
    bl hook_CheckTingle

.section .patch_TingleCheckClocktownMapTwo
.global patch_TingleCheckClocktownMapTwo
patch_TingleCheckClocktownMapTwo:
    mov r0,#0x1
    bl hook_CheckTingleTwo

.section .patch_TingleCheckWoodfallMapTwo
.global patch_TingleCheckWoodfallMapTwo
patch_TingleCheckWoodfallMapTwo:
    mov r0,#0x2
    bl hook_CheckTingleTwo

.section .patch_TingleCheckSnowheadMapTwo
.global patch_TingleCheckSnowheadMapTwo
patch_TingleCheckSnowheadMapTwo:
    mov r0,#0x4
    bl hook_CheckTingleTwo

.section .patch_TingleCheckRomaniMapTwo
.global patch_TingleCheckRomaniMapTwo
patch_TingleCheckRomaniMapTwo:
    mov r0,#0x8
    bl hook_CheckTingleTwo

.section .patch_TingleCheckGreatBayMapTwo
.global patch_TingleCheckGreatBayMapTwo
patch_TingleCheckGreatBayMapTwo:
    mov r0,#0x10
    bl hook_CheckTingleTwo

.section .patch_TingleCheckStoneTowerMapTwo
.global patch_TingleCheckStoneTowerMapTwo
patch_TingleCheckStoneTowerMapTwo:
    mov r0,#0x20
    bl hook_CheckTingleTwo