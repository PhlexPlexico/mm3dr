.arm

.section .patch_LoadExtData
.global patch_LoadExtData
patch_LoadExtData:
    bl hook_SaveFile_Load

.section .patch_SaveFile_init
.global patch_SaveFile_init
patch_SaveFile_init:
    bl hook_SaveFile_Init

.section .patch_SaveExtDataOnOwl
.global patch_SaveExtDataOnOwl
patch_SaveExtDataOnOwl:
    b hook_OwlExtDataSave