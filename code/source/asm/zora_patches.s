.arm


.section .patch_ThirdZoraSwimCheck
.global patch_ThirdZoraSwimCheck
patch_ThirdZoraSwimCheck:
    bl hook_ThirdZoraSwimCheck

.section .patch_FirstZoraSwimCheck
.global patch_FirstZoraSwimCheck
patch_FirstZoraSwimCheck:
    bl hook_FirstZoraSwimCheck

.section .patch_SecondZoraSwimCheck
.global patch_SecondZoraSwimCheck
patch_SecondZoraSwimCheck:
    bl hook_SecondZoraSwimCheck