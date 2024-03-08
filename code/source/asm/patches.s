.arm

.section .patch_DecoupleZlZr
.global patch_DecoupleZlZr
patch_DecoupleZlZr:
    b 0x0116718

.section .patch_startHeap
.global patch_startHeap
patch_startHeap:
    bl hook_Start

.section .patch_FixSurroundSound
.global patch_FixSurroundSound
patch_FixSurroundSound:
    nop
    nop
    nop
    nop
    nop

@ nop gctx->field_22f8 from being potentially nulled. Disables stray fairy respawn and doors locking.
.section .patch_DoNotResetPermFlags
.global patch_DoNotResetPermFlags
patch_DoNotResetPermFlags:
    nop
    nop
    nop
    nop

.section .patch_OcarinaDive
.global patch_OcarinaDive
patch_OcarinaDive:
    bl hook_CheckOcarinaDive

.section .patch_MainLoop
.global patch_MainLoop
patch_MainLoop:
    b hook_MainLoop

.section .patch_DecoupleStartSelect
.global patch_DecoupleStartSelect
patch_DecoupleStartSelect:
    nop

.section .patch_AwakeCallback
.global AwakeCallback_patch
AwakeCallback_patch:
    b hook_Gfx_AwakeCallback

.section .patch_SleepQueryCallback
.global SleepQueryCallback_patch
SleepQueryCallback_patch:  
    b hook_Gfx_SleepQueryCallback

.section .patch_Gfx_Update
.global Gfx_Update_patch
Gfx_Update_patch:
    b hook_Gfx_Update

.section .patch_OverrideBombersNotebook
.global patch_OverrideBombersNotebook
patch_OverrideBombersNotebook:
    b hook_OverrideHMSBombers

.section .patch_KeepBowOnEpona
.global patch_KeepBowOnEpona
patch_KeepBowOnEpona:
    nop

.section .patch_OverrideCutsceneNextEntrance
.global patch_OverrideCutsceneNextEntrance
patch_OverrideCutsceneNextEntrance:
    bl hook_OverrideCutsceneNextEntrance

@ There's a while loop located in the event
@ timer that checks if we have mystery milk.
@ We do not wish to show this since we want to remove
@ the timer, so we just nop the branch.
.section .patch_RemoveMysteryMilkTimer
.global patch_RemoveMysteryMilkTimer
patch_RemoveMysteryMilkTimer:
    nop

@ Skip past all the fairy and 
@ door resetting if we are the temples
@ as we don't want to softlock users
@ if they have already used their keys.
.section .patch_DoNotResetTempleFlags
.global patch_DoNotResetTempleFlags
patch_DoNotResetTempleFlags:
    bl hook_DoNotResetTempleFlags


@ Skips past a loop that resets all
@ values in the each dungeon for 
@ keys/fairies/boss key/etc
@ to zero. Small QoL if boss
@ keys are already given, same with keys
.section .patch_DoNotRemoveKeys
.global patch_DoNotRemoveKeys
patch_DoNotRemoveKeys:
    nop
    nop
    nop
    nop
    nop
    nop
    nop

.section .patch_RemoveDekuMaskCheckSoT
.global patch_RemoveDekuMaskCheckSoT
patch_RemoveDekuMaskCheckSoT:
    b 0x1D80AC

@ Avoids all the check items for mystery milk so we can use items freely.
.section .patch_RemoveMysteryMilkUsabilityCheck
.global patch_RemoveMysteryMilkUsabilityCheck
patch_RemoveMysteryMilkUsabilityCheck:
    nop

.section .patch_SpawnFastElegyStatues
.global patch_SpawnFastElegyStatues
patch_SpawnFastElegyStatues: 
    b hook_SpawnFastElegyStatues

.section .patch_CheckDungeonItems
.global patch_CheckDungeonItems
patch_CheckDungeonItems:
    bl hook_CheckDungeonItems

.section .patch_CheckDungeonSmallKeys
.global patch_CheckDungeonSmallKeys
patch_CheckDungeonSmallKeys:
    bl hook_CheckDungeonSmallKeys

.section .patch_DisableMilkTimer
.global patch_DisableMilkTimer
patch_DisableMilkTimer:
    nop

.section .patch_GetCustomText
.global patch_GetCustomText
patch_GetCustomText:
    b GetMessageFromId

@ This removes the song of saoring check for the mystery milk.
@ We can now soar freely.
.section .patch_RemoveMysteryMilkSoSCheck
.global patch_RemoveMysteryMilkSoSCheck
patch_RemoveMysteryMilkSoSCheck:
    mov r0, #0x0

.section .patch_BlastMaskCooldown
.global patch_BlastMaskCooldown
patch_BlastMaskCooldown:
    bl hook_BlastMaskCooldown

.section .patch_RemoveRemainsStateCheck
.global patch_RemoveRemainsStateCheck
patch_RemoveRemainsStateCheck:
    b hook_RemainsCheckValue

.section .patch_OverrideBomberTextID
.global OverrideBomberTextID_patch
OverrideBomberTextID_patch:
    b hook_OverrideBomberTextID

.section .patch_EnteringLocation
.global patch_EnteringLocation
patch_EnteringLocation:
    bl hook_EnteringLocation

.section .patch_ReadGamePad
.global patch_ReadGamePad
patch_ReadGamePad:
    b hook_readGamePad

.section .patch_DisableExistingTrigger
.global patch_DisableExistingTrigger
patch_DisableExistingTrigger:
    b 0x059bb60 @branches past all the checks for button presses and whatnot. We override all of this.

.section .patch_ItemCloseOnSelect
.global patch_ItemCloseOnSelect
patch_ItemCloseOnSelect:
    tst r1, #14

@ Adjusts ocarina songs to be in-line with restoration
.section .patch_HandleOcarinaHooks
.global patch_HandleOcarinaHooks
patch_HandleOcarinaHooks:
    b hook_HandleOcarina

.section .patch_FasterBlockMovement
.global patch_FasterBlockMovement
patch_FasterBlockMovement:
    .float 50.0

.section .patch_FasterBlockMovementBack
.global patch_FasterBlockMovementBack
patch_FasterBlockMovementBack:
    .float 60.0

@ nop a bne statement to allow ice arrows to be used on any water surface.
.section .patch_IceArrowsAnywhere
.global patch_IceArrowsAnywhere
patch_IceArrowsAnywhere:
    nop

@ Removes a check to see if the GID is a small key.
.section .patch_AdjustMapAndCompassChests
.global patch_AdjustMapAndCompassChests
patch_AdjustMapAndCompassChests:
    bl hook_checkChestContentSetting


.section .patch_RemoveSongCheckKaepora
.global patch_RemoveSongCheckKaepora
patch_RemoveSongCheckKaepora:
    bl hook_CheckKaeporaSpawn
    nop

.section .patch_changeChestTypeToMatchContents
.global patch_changeChestTypeToMatchContents
patch_changeChestTypeToMatchContents:
    bl hook_changeChestTypeToMatchContents

.section .patch_RemoveZoraMaskCheckMikau
.global patch_RemoveZoraMaskCheckMikau
patch_RemoveZoraMaskCheckMikau:
    b hook_MikauRewardCheck

.section .patch_AromaItemCheck
.global patch_AromaItemCheck
patch_AromaItemCheck:
    b hook_AromaItemCheck

.section .patch_CheckMoTRequirement
.global patch_CheckMoTRequirement
patch_CheckMoTRequirement:
    b hook_CheckMoTSetting

.section .patch_RemoveBombers
.global patch_RemoveBombers
patch_RemoveBombers:
    nop

.section .patch_RemoveSoHMaskAppearing
.global patch_RemoveSoHMaskAppearing
patch_RemoveSoHMaskAppearing:
    nop

.section .patch_CheckMasksOnMoon
.global patch_CheckMasksOnMoon
patch_CheckMasksOnMoon:
    bl hook_CheckMasksOnMoon

.section .patch_RemoveJimWhenExitingHideout
.global RemoveJimWhenExitingHideout_patch
RemoveJimWhenExitingHideout_patch:
    cmp r0,r0

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader