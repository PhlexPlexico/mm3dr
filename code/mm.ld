OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS{

	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}

	/* .patch_startHeap 0x0103ec8 : {
		*(.patch_startHeap)
	} */

	.patch_MainLoop 0x10676C : {
		*(.patch_MainLoop)
	}

	.patch_DecoupleZlZr 0x1166C8 :  {
		*(.patch_DecoupleZlZr)
	}

	.patch_DecoupleStartSelect 0x121ee8 : {
		*(.patch_DecoupleStartSelect)
	} 

	.patch_ISGCrouchStabOne 0x1D32E0 : {
		*(.patch_ISGCrouchStabOne)
	}

    .patch_ISGCrouchStabTwo 0x1DBEA4 : {
		*(.patch_ISGCrouchStabTwo)
	}

	.patch_fasterBlockMovement 0x2AC634 : {
		*(.patch_fasterBlockMovement)
	}

	.patch_fasterBlockMovementBack 0x2D0C0C : {
		*(.patch_fasterBlockMovementBack)
	}

	.patch_IncomingGetItemID 0x4B1394 : {
		*(.patch_IncomingGetItemID)
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
		rCustomMessages = . ;
        __text_end  = . ;
    }
}