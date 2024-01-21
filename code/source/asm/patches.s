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

.section .patch_OcarinaDive
.global patch_OcarinaDive
patch_OcarinaDive:
    bl hook_CheckOcarinaDive

.section .patch_IncomingGetItemID
.global IncomingGetItemID_patch
IncomingGetItemID_patch:
    bl hook_IncomingGetItemID

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

@ This should remove the overwriting message for when the
@ user receives the Zora Mask.
@ Largely untested, need to check for any UB.
.section .patch_RemoveSOHCutesceneAfterMessage
.global patch_RemoveSOHCutesceneAfterMessage
patch_RemoveSOHCutesceneAfterMessage:
    b hook_ChangeSOHToCustomText

.section .patch_OverrideBombersNotebook
.global patch_OverrideBombersNotebook
patch_OverrideBombersNotebook:
    b hook_OverrideHMSBombers


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

@ Skip past all chest content resetting.
@ Since this is rando, we don't want users
@ getting chests again, and instead of
@ keeping track via extdata we can just 
@ branch over everything in relation to 
@ resetting all the chests in the game.
.section .patch_AttemptKeepChestsClosed
.global patch_AttemptKeepChestsClosed
patch_AttemptKeepChestsClosed:
    b 0x01c936c

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

@ NOP out the bit of code that checks your sword and gives it back if it 
@ is not a razor sword. This should prevent us from ever getting Kokiri sword on 
@ cycle reset.
.section .patch_DoNotGiveSwordBackOnReset
.global patch_DoNotGiveSwordBackOnReset
patch_DoNotGiveSwordBackOnReset:
    bl hook_DoNotGiveSwordBackOnReset

.section .patch_RemoveItemBUsabilityOnReset
.global patch_RemoveItemBUsabilityOnReset
patch_RemoveItemBUsabilityOnReset:
    bl hook_DoNotGiveSwordBackOnResetTwo

.section .patch_RemoveSwordFlagsOnReset
.global patch_RemoveSwordFlagsOnReset
patch_RemoveSwordFlagsOnReset:
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

.section .patch_CheckCurrentInventoryOverrideItem
.global patch_CheckCurrentInventoryOverrideItem
patch_CheckCurrentInventoryOverrideItem:
    b hook_CheckCurrentInventory

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

.section .patch_LoadExtData
.global patch_LoadExtData
patch_LoadExtData:
    bl hook_SaveFile_Load

.section .patch_SaveFile_init
.global patch_SaveFile_init
patch_SaveFile_init:
    bl hook_SaveFile_Init

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

.section .patch_OverrideItemIdIndex
.global patch_OverrideItemIdIndex
patch_OverrideItemIdIndex:
@TODO: Branch off to hook and load addr that is needed from text ID.
    bl hook_OverrideItemIdIndex

.section .patch_RemoveRemainsStateCheck
.global patch_RemoveRemainsStateCheck
patch_RemoveRemainsStateCheck:
    b hook_RemainsCheckValue

.section .patch_ChangeDrawItemIndex
.global OverrideDrawIndex_patch
OverrideDrawIndex_patch:
    b hook_OverrideDrawIndex

.section .patch_ChangeDrawItemIndexSecond
.global patch_ChangeDrawItemIndexSecond
patch_ChangeDrawItemIndexSecond:
    b hook_OverrideDrawIndexSecond

.section .patch_OverrideTextID
.global OverrideTextID_patch
OverrideTextID_patch:
    b hook_OverrideTextID

.section .patch_OverrideBomberTextID
.global OverrideBomberTextID_patch
OverrideBomberTextID_patch:
    b hook_OverrideBomberTextID

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    b hook_OverrideItemID

.section .patch_RemoveGoronMaskCheckDarmani
.global patch_RemoveGoronMaskCheckDarmani
patch_RemoveGoronMaskCheckDarmani:
    b hook_DarmaniRewardCheck

.section .patch_OverrideQuiverArchery
.global patch_OverrideQuiverArchery
patch_OverrideQuiverArchery:
    mov r2,#0x47

.section .patch_OverrideQuiverArcheryTwo
.global patch_OverrideQuiverArcheryTwo
patch_OverrideQuiverArcheryTwo:
    mov r2,#0x47

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

@ Remove call from twinmold->life -= twinmold_min_damage.
@ .section .patch_TwinmoldConsistentDamage
@ .global patch_TwinmoldConsistentDamage
@ patch_TwinmoldConsistentDamage:
@     nop

.section .patch_FasterBlockMovement
.global patch_FasterBlockMovement
patch_FasterBlockMovement:
    .float 50.0

@ Removes sword being removed from inventory during 
.section .patch_DoNotRemoveSwordGabora
.global patch_DoNotRemoveSwordGabora
patch_DoNotRemoveSwordGabora:
    nop

.section .patch_FasterBlockMovementBack
.global patch_FasterBlockMovementBack
patch_FasterBlockMovementBack:
    .float 60.0

.section .patch_SaveExtDataOnOwl
.global patch_SaveExtDataOnOwl
patch_SaveExtDataOnOwl:
    b hook_OwlExtDataSave

@ nop a bne statement to allow ice arrows to be used on any water surface.
.section .patch_IceArrowsAnywhere
.global patch_IceArrowsAnywhere
patch_IceArrowsAnywhere:
    nop

.section .patch_RemoveZoraMaskCheckMikau
.global patch_RemoveZoraMaskCheckMikau
patch_RemoveZoraMaskCheckMikau:
    b hook_MikauRewardCheck

.section .patch_AromaItemCheck
.global patch_AromaItemCheck
patch_AromaItemCheck:
    b hook_AromaItemCheck

.section .patch_OverrideProgessiveWallet
.global patch_OverrideProgessiveWallet
patch_OverrideProgessiveWallet:
@Override to use the progressive wallet instead.
    mov r2,#0x48

.section .patch_OverrideProgessiveWalletTwo
.global patch_OverrideProgessiveWalletTwo
patch_OverrideProgessiveWalletTwo:
@Override to use the progressive wallet instead.
    mov r2,#0x48

.section .patch_CheckMoTRequirement
.global patch_CheckMoTRequirement
patch_CheckMoTRequirement:
    b hook_CheckMoTSetting

.section .patch_HMSGiveItem
.global patch_HMSGiveItem
patch_HMSGiveItem:
    b hook_OverrideHMSDekuMask

.section .patch_RemoveBombers
.global patch_RemoveBombers
patch_RemoveBombers:
    nop

.section .patch_GoronMaskGiveItem
.global patch_GoronMaskGiveItem
patch_GoronMaskGiveItem:
    b hook_GoronMaskGiveItem

.section .patch_ZoraMaskGiveItem
.global patch_ZoraMaskGiveItem
patch_ZoraMaskGiveItem:
    b hook_ZoraMaskGiveItem

.section .patch_RemoveSoHMaskAppearing
.global patch_RemoveSoHMaskAppearing
patch_RemoveSoHMaskAppearing:
    nop
    
.section .patch_GibdoMaskGiveItem
.global patch_GibdoMaskGiveItem
patch_GibdoMaskGiveItem:
    b hook_GibdoMaskGiveItem

.section .patch_CouplesMaskGiveItem
.global patch_CouplesMaskGiveItem
patch_CouplesMaskGiveItem:
    b hook_CouplesMaskGiveItem

.section .patch_RemoveCouplesMaskMessage
.global patch_RemoveCouplesMaskMessage
patch_RemoveCouplesMaskMessage:
    b hook_AdjustCouplesMaskMessage

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader