OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS{

  . = 0x100000;

  .patch_loader 0x100000 : {
    *(.patch_loader)
  }

  .patch_startHeap 0x010001C : {
    *(.patch_startHeap)
  }

  .patch_MainLoop 0x10676C : {
    *(.patch_MainLoop)
  }

  .patch_DecoupleZlZr 0x1166C8 : {
    *(.patch_DecoupleZlZr)
  }

  .patch_DecoupleStartSelect 0x121EE8 : {
    *(.patch_DecoupleStartSelect)
  }

  .patch_AwakeCallback 0x124DE8 : {
		*(.patch_AwakeCallback)
	}

  .patch_SleepQueryCallback 0x124DF0 : {
		*(.patch_SleepQueryCallback)
	}

  .patch_Gfx_Update 0x1376DC : {
    *(.patch_Gfx_Update)
  }

  .patch_FixSurroundSound 0x1404E8 : {
    *(.patch_FixSurroundSound)
  }

  .patch_PostActorCalc 0x174E08 : {
    *(.patch_PostActorCalc)
  }

  .patch_RemoveCouplesMaskMessage 0x1867C4 : {
    *(.patch_RemoveCouplesMaskMessage)
  }

  .patch_RemoveSOHCutesceneAfterMessage 0x186810 : {
    *(.patch_RemoveSOHCutesceneAfterMessage)
  }

  .patch_OverrideBombersNotebook 0x186ACC : {
    *(.patch_OverrideBombersNotebook)
  }

  /*2bec9c GOOD DREAM */
  /*  
  .patch_RemoveMeetMaskCutScene 0x2bec9c : {
    *(.patch_RemoveMeetMaskCutScene)
  } */

  .patch_KeepBowOnEpona 0x188794 : {
    *(.patch_KeepBowOnEpona)
  }

  .patch_RemoveTradeItemFromSlot 0x1AFE94 : {
    *(.patch_RemoveTradeItemFromSlot)
  }

  .patch_SwapTradeItemFromExtSlot 0x1AFEA8 : {
    *(.patch_SwapTradeItemFromExtSlot)
  }

  .patch_OverrideCutsceneNextEntrance 0x1B1834 : {
    *(.patch_OverrideCutsceneNextEntrance)
  }

  .patch_RemoveMysteryMilkTimer 0x1B7A54 : {
    *(.patch_RemoveMysteryMilkTimer)
  }

  .patch_GetCustomText 0x1BDE78 : {
    *(.patch_GetCustomText)
  }

  .patch_DoNotResetTempleFlags 0x1C936C : {
    *(.patch_DoNotResetTempleFlags)
  }

  .patch_DoNotResetPermFlags 0x1C9348 : {
    *(.patch_DoNotResetPermFlags)
  }

  .patch_DoNotRemoveTradeItems 0x1c9AA8 : {
    *(.patch_DoNotRemoveTradeItems)
  }

  .patch_DoNotRemoveKeys 0x1C9B94 : {
    *(.patch_DoNotRemoveKeys)
  }

  .patch_DoNotGiveSwordBackOnReset 0x1C98DC : {
    *(.patch_DoNotGiveSwordBackOnReset)
  }

  .patch_OverrideBomberTextID 0x1D2764 : {
    *(.patch_OverrideBomberTextID)
  }

  .patch_ISGCrouchStabOne 0x1D32E0 : {
    *(.patch_ISGCrouchStabOne)
  }

  .patch_RemoveDekuMaskCheckSoT 0x1D8008 : {
    *(.patch_RemoveDekuMaskCheckSoT)
  }

  .patch_RemoveMysteryMilkSoSCheck 0x1D79F8 : {
    *(.patch_RemoveMysteryMilkSoSCheck)
  }

  .patch_DoNotForceMaskChange 0x1DB314 : {
    *(.patch_DoNotForceMaskChange)
  }

  .patch_HandleFastMaskTransforms 0x1DB744 : {
    *(.patch_HandleFastMaskTransforms)
  }

  .patch_ISGCrouchStabTwo 0x1DBEA4 : {
    *(.patch_ISGCrouchStabTwo)
  }

  .patch_RemoveMysteryMilkUsabilityCheck 0x1E04D8 : {
    *(.patch_RemoveMysteryMilkUsabilityCheck)
  }

  .patch_OcarinaDive 0x1E1F0C : {
    *(.patch_OcarinaDive)
  }

  .patch_ByPassMaskEquipmentChecks 0x1E770C : {
    *(.patch_ByPassMaskEquipmentChecks)
  }

  .patch_SpawnFastElegyStatues 0x1E9FB8 : {
    *(.patch_SpawnFastElegyStatues)
  }

  .patch_FastTransformCutsceneSkipBtns 0x1EB660 : {
    *(.patch_FastTransformCutsceneSkipBtns)
  }

  .patch_BypassFirstPersonModeChecks 0x1EDFB4 : {
    *(.patch_BypassFirstPersonModeChecks)
  } 

  .patch_ZoraInWaterFastSwim 0x1F0C78 : {
    *(.patch_ZoraInWaterFastSwim)
  }

  .patch_CheckCurrentInventoryOverrideItem 0x1F3D5C : {
    *(.patch_CheckCurrentInventoryOverrideItem)
  }

  /* .patch_OverrideItemIDFour 0x1FBD10 : {
    *(.patch_OverrideItemIdIndex)
  } */

  /* .patch_OverrideItemIDThree 0x1FF604 : {
    *(.patch_OverrideItemIdIndex)
  } */

  .patch_RemoveGoronRollChecksWithoutMask 0x1F78CC : {
    *(.patch_RemoveGoronRollChecksWithoutMask)
  }

  .patch_FifthZoraSwimCheck 0x1FFA84 : {
    *(.patch_FifthZoraSwimCheck)
  }

  .patch_UseZoraASwimSecond 0x1FFD74 : {
    *(.patch_UseZoraASwimSecond)
  }

  .patch_ThirdZoraSwimCheck 0x1FFDBC : {
    *(.patch_ThirdZoraSwimCheck)
  }

  .patch_CheckMagicForZoraFastSwim 0x1FFDE8 : {
    *(.patch_CheckMagicForZoraFastSwim)
  }

  .patch_BlastMaskCooldown 0x2047FC : {
    *(.patch_BlastMaskCooldown)
  }

  .patch_ZoraBarrierCheckMagicAcquired 0x207230 : {
    *(.patch_ZoraBarrierCheckMagicAcquired)
  }

  .patch_RemoveRSHealthOne 0x20826C : {
    *(.patch_RemoveRazordSwordHealth)
  }

  .patch_RemoveRSHealthTwo 0x20843C : {
    *(.patch_RemoveRazordSwordHealthTwo)
  }

  .patch_OverrideItemIdIndex 0x21D124 : {
    *(.patch_OverrideItemIdIndex)
  }

  .patch_ChangeTriggerAandRToA 0x220EFC : {
    *(.patch_ChangeTriggerAandRToA)
  }

  .patch_FourthZoraSwimCheck 0x220F2C : {
    *(.patch_FourthZoraSwimCheck)
  }

  .patch_FirstZoraSwimCheck 0x220F60 : {
    *(.patch_FirstZoraSwimCheck)
  }

  .patch_SecondZoraSwimCheck 0x2210DC : {
    *(.patch_SecondZoraSwimCheck)
  }

  .patch_ForceSwordUpgradeOnHuman 0x233D88 : {
    *(.patch_ForceSwordUpgradeOnHuman)
  }

  .patch_CheckDungeonItems 0x233F30 : {
    *(.patch_CheckDungeonItems)
  }

  .patch_CheckDungeonSmallKeys 0x233F4C : {
    *(.patch_CheckDungeonSmallKeys)
  }

	.patch_DisableMilkTimer 0x234BFC : {
		*(.patch_DisableMilkTimer)
	}

  .patch_RemoveRSHealthThree 0x235800 : {
    *(.patch_RemoveRazordSwordHealthThree)
  }

  .patch_RemoveRemainsStateCheck 0x22B7BC : {
    *(.patch_RemoveRemainsStateCheck)
  }

  .patch_ChangeDrawItemIndex 0x22F24C : {
    *(.patch_ChangeDrawItemIndex)
  }

  .patch_ChangeDrawItemIndexSecond 0x22F474 : {
    *(.patch_ChangeDrawItemIndexSecond)
  }

  .patch_OverrideTextID 0x2310FC : {
    *(.patch_OverrideTextID)
  }

  .patch_OverrideItemID 0x231108 : {
    *(.patch_OverrideItemID)
  }

  .patch_EnteringLocation 0x23AA54 : {
    *(.patch_EnteringLocation)
  }

  .patch_TwinmoldConsistentDamage 0x28E544 : {
    *(.patch_TwinmoldConsistentDamage)
  }

  .patch_FasterBlockMovement 0x2AC634 : {
    *(.patch_FasterBlockMovement)
  }

  .patch_GaboraCheckExtDataNotSword 0x2CBB14 : {
    *(.patch_GaboraCheckExtDataNotSword)
  }

  .patch_DoNotRemoveSwordGaboraOne 0x2CBCB0 : {
    *(.patch_DoNotRemoveSwordGabora)
  }

  .patch_DoNotRemoveSwordGaboraTwo 0x2CBCC0 : {
    *(.patch_DoNotRemoveSwordGaboraTwo)
  }

  .patch_FasterBlockMovementBack 0x2D0C0C : {
    *(.patch_FasterBlockMovementBack)
  }

  .patch_TingleCheckClocktownMap 0x2DABD0 : {
    *(.patch_TingleCheckClocktownMap)
  }

  .patch_TingleCheckWoodfallMap 0x2DABE4 : {
    *(.patch_TingleCheckWoodfallMap)
  }

  .patch_TingleCheckSnowheadMap 0x2DABF8 : {
    *(.patch_TingleCheckSnowheadMap)
  }

  .patch_TingleCheckRomaniMap 0x2DAC0C : {
    *(.patch_TingleCheckRomaniMap)
  }

  .patch_TingleCheckGreatBayMap 0x2DAC20 : {
    *(.patch_TingleCheckGreatBayMap)
  }

  .patch_TingleCheckStoneTowerMap 0x2DAC30 : {
    *(.patch_TingleCheckStoneTowerMap)
  }

  .patch_RemoveGoronMaskCheckDarmani 0x2DE788 : {
    *(.patch_RemoveGoronMaskCheckDarmani)
  }

  .patch_CheckOshExtData 0x3BF224 : {
    *(.patch_CheckOshExtData)
  }

  .patch_OverrideQuiverArcheryTown 0x3E50E4 : {
    *(.patch_OverrideQuiverArchery)
  }

  .patch_OverrideQuiverArcherySwamp 0x3EA2B0 : {
    *(.patch_OverrideQuiverArcheryTwo)
  }

  .patch_OverrideFairyGiveItem 0x3BECAC : {
    *(.patch_OverrideFairyGiveItem)
  }

  .patch_OverrideGreatFairySpawn 0x3BEC84 : {
    *(.patch_OverrideGreatFairySpawn)
  }

  .patch_SaveExtDataOnOwl 0x317004 : {
    *(.patch_SaveExtDataOnOwl)
  }

  .patch_IceArrowsAnywhere 0x31874C : {
    *(.patch_IceArrowsAnywhere)
  }

  .patch_changeChestTypeToMatchContents 0x31CE0C : {
    *(.patch_changeChestTypeToMatchContents)
  }

  .patch_AdjustMapAndCompassChests 0x31CE9C : {
    *(.patch_AdjustMapAndCompassChests)
  }

  .patch_RemoveZoraMaskCheckMikau 0x32BBB8 : {
    *(.patch_RemoveZoraMaskCheckMikau)
  }

  .patch_AromaItemCheck 0x35091C : {
    *(.patch_AromaItemCheck)
  }

  .patch_CheckMoTRequirement 0x35C428 : {
    *(.patch_CheckMoTRequirement)
  }

  .patch_TradeItemDeleteMoonsTear 0x3B5214 : {
    *(.patch_TradeItemDeleteMoonsTear)
  }

  .patch_OverrideWalletSpiderHouseTwo 0x3BF078 : {
    *(.patch_OverrideWalletSpiderHouseTwo)
  }

  .patch_OverrideWalletSpiderHouse 0x3BF2A8 : {
    *(.patch_OverrideWalletSpiderHouse)
  }

  .patch_HMSGiveItem 0x41D018 : {
    *(.patch_HMSGiveItem)
  }

  .patch_GoronMaskGiveItem 0x41DAB0 : {
    *(.patch_GoronMaskGiveItem)
  }

  .patch_ZoraMaskGiveItem 0x41DB80 : {
    *(.patch_ZoraMaskGiveItem)
  }

  /* .patch_RemoveSoHMaskAppearing 0x41DB98 : {
    *(.patch_RemoveSoHMaskAppearing)
  } */

  .patch_GibdoMaskGiveItem 0x41DC48 : {
    *(.patch_GibdoMaskGiveItem)
  }

  .patch_OverrideBankerWalletReward 0x459044 : {
    *(.patch_OverrideProgessiveWalletTwo)
  }

  .patch_CouplesMaskGiveItem 0x46E228 : {
    *(.patch_CouplesMaskGiveItem)
  }

  .patch_TradeItemDeleteLandTitleDeed 0x477710 : {
    *(.patch_TradeItemDeleteLandTitleDeed)
  }

   .patch_TradeItemDeleteSwampTitleDeed 0x47771C : {
    *(.patch_TradeItemDeleteSwampTitleDeed)
  }

  .patch_TradeItemDeleteMountainTitleDeed 0x477728 : {
    *(.patch_TradeItemDeleteMountainTitleDeed)
  }

  .patch_LoadExtData 0x48C760 : {
    *(.patch_LoadExtData)
  }

  .patch_RemoveKafeiItemFromExtSlot 0x4AD1B8 : {
    *(.patch_RemoveKafeiItemFromExtSlot)
  }

  .patch_IncomingGetItemID 0x4B1394 : {
    *(.patch_IncomingGetItemID)
  }

  .patch_RemoveJimWhenExitingHideout 0x4B6964 : {
    *(.patch_RemoveJimWhenExitingHideout)
  }

  .patch_ReadGamePad 0x59BA10 : {
    *(.patch_ReadGamePad)
  }

  .patch_DisableExistingTrigger 0x59BA14 : {
    *(.patch_DisableExistingTrigger)
  }

  .patch_SwapStoredTradeItems 0x5a6b44 : {
    *(.patch_SwapStoredTradeItems)
  }

  .patch_ShorterAnimationOpen 0x5B1758 : {
    *(.patch_ShorterAnimationOpenOne)
  }

  .patch_ShorterAnimationNewTextOne 0x5B1780 : {
    *(.patch_ShorterAnimationOpenTwo)
  }

  .patch_ShorterAnimationNewTextTwo 0x5B1A7C : {
    *(.patch_ShorterAnimationOpenThree)
  }

  .patch_ShorterAnimationUnk 0x5B1A80 : {
    *(.patch_ShorterAnimationOpenFour)
  }

  .patch_ShorterAnimationMainText 0x5B1A8C : {
    *(.patch_ShorterAnimationOpenFive)
  }

  .patch_ShorterAnimationStateFailed 0x5B1A90 : {
    *(.patch_ShorterAnimationOpenSix)
  }

  .patch_ShorterAnimationFail 0x5B183C : {
    *(.patch_ShorterAnimationFail)
  }

  /*0x05ffc70*/ /*0x177ddc*/ /*0x5bbab8 */ /* 0x5b8b24 */
	.patch_SaveFile_init 0x5B8B24 : {
		*(.patch_SaveFile_init)
	}

  .patch_ItemCloseOnSelect 0x5C19E4 : {
    *(.patch_ItemCloseOnSelect)
  }

  .patch_HandleOcarinaHooks 0x604D8C : {
    *(.patch_HandleOcarinaHooks)
  }

  . = 0x61CD8C;
	/* Addr already 4 byte aligned! */
	/* . = ALIGN(4); */
	.loader : {
		*(.loader*)
	}

  . = 0x007D0000;
    .text : {
        __text_start = . ;
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.data)
        *(.bss)
        *(COMMON)
        __text_end  = . ;
  }
}