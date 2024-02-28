.arm


.section .patch_PostActorCalc
.global patch_PostActorCalc
patch_PostActorCalc:
  bl hook_PostActorCalc

@ Remove call from twinmold->life -= twinmold_min_damage.
.section .patch_TwinmoldConsistentDamage
.global patch_TwinmoldConsistentDamage
patch_TwinmoldConsistentDamage:
    bl hook_TwinmoldConsistentDamage
