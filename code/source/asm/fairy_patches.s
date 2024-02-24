.arm

.section .patch_OverrideFairyGiveItem
.global OverrideFairyItemID_patch
OverrideFairyItemID_patch:
    b hook_OverrideFairyItem

.section .patch_OverrideGreatFairySpawn
.global OverrideGreatFairySpawn_patch
OverrideGreatFairySpawn_patch:
    nop
    @ldmia sp!,{r4 - r6, pc}
    @ldmia sp !, {r4 - r6, lr}
    @ bx lr