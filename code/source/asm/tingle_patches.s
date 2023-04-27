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