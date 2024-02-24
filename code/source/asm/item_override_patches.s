.arm

.section .patch_IncomingGetItemID
.global IncomingGetItemID_patch
IncomingGetItemID_patch:
    bl hook_IncomingGetItemID


.section .patch_CheckCurrentInventoryOverrideItem
.global patch_CheckCurrentInventoryOverrideItem
patch_CheckCurrentInventoryOverrideItem:
    b hook_CheckCurrentInventory

.section .patch_OverrideItemIdIndex
.global patch_OverrideItemIdIndex
patch_OverrideItemIdIndex:
@TODO: Branch off to hook and load addr that is needed from text ID.
    bl hook_OverrideItemIdIndex

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

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    b hook_OverrideItemID

.section .patch_RemoveGoronMaskCheckDarmani
.global patch_RemoveGoronMaskCheckDarmani
patch_RemoveGoronMaskCheckDarmani:
    b hook_DarmaniRewardCheck

.section .patch_CheckOshExtData
.global patch_CheckOshExtData
patch_CheckOshExtData:
    bl hook_CheckOshExtData

.section .patch_OverrideQuiverArchery
.global patch_OverrideQuiverArchery
patch_OverrideQuiverArchery:
    mov r2,#0x47

.section .patch_OverrideQuiverArcheryTwo
.global patch_OverrideQuiverArcheryTwo
patch_OverrideQuiverArcheryTwo:
    mov r2,#0x47

.section .patch_OverrideWalletSpiderHouseTwo
.global patch_OverrideWalletSpiderHouseTwo
patch_OverrideWalletSpiderHouseTwo:
@Override to use the progressive wallet instead.
    mov r2,#0x48

.section .patch_OverrideWalletSpiderHouse
.global patch_OverrideWalletSpiderHouse
patch_OverrideWalletSpiderHouse:
@Override to use the progressive wallet instead.
    mov r2,#0x48

.section .patch_OverrideProgessiveWalletTwo
.global patch_OverrideProgessiveWalletTwo
patch_OverrideProgessiveWalletTwo:
@Override to use the progressive wallet instead.
    mov r2,#0x48

.section .patch_GoronMaskGiveItem
.global patch_GoronMaskGiveItem
patch_GoronMaskGiveItem:
    b hook_GoronMaskGiveItem

.section .patch_ZoraMaskGiveItem
.global patch_ZoraMaskGiveItem
patch_ZoraMaskGiveItem:
    b hook_ZoraMaskGiveItem

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


@ This should remove the overwriting message for when the
@ user receives the Zora Mask.
@ Largely untested, need to check for any UB.
.section .patch_RemoveSOHCutesceneAfterMessage
.global patch_RemoveSOHCutesceneAfterMessage
patch_RemoveSOHCutesceneAfterMessage:
    b hook_ChangeSOHToCustomText
