.arm

.section .patch_ZoraInWaterFastSwim
.global patch_ZoraInWaterFastSwim
patch_ZoraInWaterFastSwim:
    bl hook_ZoraInWaterFastSwim

.section .patch_FifthZoraSwimCheck
.global patch_FifthZoraSwimCheck
patch_FifthZoraSwimCheck:
    bl hook_FifthZoraSwimCheck

.section .patch_UseZoraASwimSecond
.global patch_UseZoraASwimSecond
patch_UseZoraASwimSecond:
    bl hook_UseZoraASwimSecond

.section .patch_ThirdZoraSwimCheck
.global patch_ThirdZoraSwimCheck
patch_ThirdZoraSwimCheck:
    bl hook_ThirdZoraSwimCheck

.section .patch_CheckMagicForZoraFastSwim
.global patch_CheckMagicForZoraFastSwim
patch_CheckMagicForZoraFastSwim:
    bl hook_CheckMagicForZoraFastSwim

.section .patch_ZoraBarrierCheckMagicAcquired
.global patch_ZoraBarrierCheckMagicAcquired
patch_ZoraCheckMagicAcquired:
    bl hook_ZoraBarrierCheckMagicAcquired

.section .patch_ChangeTriggerAandRToA
.global patch_ChangeTriggerAandRToA
patch_ChangeTriggerAandRToA:
    bl hook_ChangeTriggerAandRToA

.section .patch_FourthZoraSwimCheck
.global patch_FourthZoraSwimCheck
patch_FourthZoraSwimCheck:
    bl hook_FourthZoraSwimCheck

.section .patch_FirstZoraSwimCheck
.global patch_FirstZoraSwimCheck
patch_FirstZoraSwimCheck:
    bl hook_FirstZoraSwimCheck

.section .patch_SecondZoraSwimCheck
.global patch_SecondZoraSwimCheck
patch_SecondZoraSwimCheck:
    bl hook_SecondZoraSwimCheck

