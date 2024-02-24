.arm
.text


.global hook_SaveFile_Load
hook_SaveFile_Load:
    push {r0-r12, lr}
    bl SaveFile_LoadExtSaveData
    pop {r0-r12, lr}
    str r5,[r1,#0x61C]
    b 0x48C764

.global hook_SaveFile_Init
hook_SaveFile_Init:
    push {r0-r12, lr}
    cpy r0,r4
    bl SaveFile_Init
    pop {r0-r12, lr}
    mov r3,#0x0
    b 0x5b8b28  


.global hook_OwlExtDataSave
hook_OwlExtDataSave:
    push {r0-r12, lr}
    bl SaveFile_SaveExtSaveData
    pop {r0-r12, lr}
    cpy r6,r0
    b 0x317008