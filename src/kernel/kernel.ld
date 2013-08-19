SECTIONS {
	/*
	 * Raspberry Pi bootloader executes at 0x8000.
	 */
	. = 0x8000;
	
	.text : {
		/*
		 * First the bootstrap code.
		 */
		*(.text.bootstrap)
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}
	
	.data : {
		*(.data)
	}

	/*
	 * The labels _bss_start and _bss_end are needed
	 * to set the whole section to 0's.
	 */
	_bss_start = .;
	.bss : {
		*(.bss)
	}
	_bss_end = .;
}
