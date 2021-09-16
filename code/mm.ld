OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}

	/* .patch_MainLoop 0x10676C : {
		*(.patch_MainLoop)
	} */

	.patch_DecoupleZlZr 0x1166C8 :  {
		*(.patch_DecoupleZlZr)
	}

	.patch_DecoupleStartSelect 0x12EAC0 : {
		*(.patch_DecoupleStartSelect)
	}

	.patch_ISGCrouchStabOne 0x1D32E0 : {
		*(.patch_ISGCrouchStabOne)
	}

    .patch_ISGCrouchStabTwo 0x1DBEA4 : {
		*(.patch_ISGCrouchStabTwo)
	}

	. = 0x61CD8C;
	. = ALIGN(4);
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