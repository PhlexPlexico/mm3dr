.arm

@ NOP out the bit of code that checks your sword and gives it back if it 
@ is not a razor sword. This should prevent us from ever getting Kokiri sword on 
@ cycle reset.
.section .patch_DoNotGiveSwordBackOnReset
.global patch_DoNotGiveSwordBackOnReset
patch_DoNotGiveSwordBackOnReset:
    bl hook_DoNotGiveSwordBackOnReset

.section .patch_ForceSwordUpgradeOnHuman
.global patch_ForceSwordUpgradeOnHuman
patch_ForceSwordUpgradeOnHuman:
    mov r0,#0x0

.section .patch_ISGCrouchStabOne
.global patch_ISGCrouchStabOne
patch_ISGCrouchStabOne:
    nop
    nop
    nop


.section .patch_ISGCrouchStabTwo
.global patch_ISGCrouchStabTwo
patch_ISGCrouchStabTwo:
    nop
    nop
    nop

.section .patch_RemoveRazordSwordHealth
.global patch_RemoveRazordSwordHealth
patch_RemoveRazordSwordHealth:
    nop

.section .patch_RemoveRazordSwordHealthTwo
.global patch_RemoveRazordSwordHealthTwo
patch_RemoveRazordSwordHealthTwo:
    nop

.section .patch_RemoveRazordSwordHealthThree
.global patch_RemoveRazordSwordHealthThree
patch_RemoveRazordSwordHealthThree:
    nop

.section .patch_GaboraCheckExtDataNotSword
.global patch_GaboraCheckExtDataNotSword
patch_GaboraCheckExtDataNotSword:
    bl hook_GaboraCheckExtDataNotSword

@ Removes sword being removed from inventory during 
.section .patch_DoNotRemoveSwordGabora
.global patch_DoNotRemoveSwordGabora
patch_DoNotRemoveSwordGabora:
    nop

@ Removes sword being removed from inventory during 
.section .patch_DoNotRemoveSwordGaboraTwo
.global patch_DoNotRemoveSwordGaboraTwo
patch_DoNotRemoveSwordGaboraTwo:
    nop