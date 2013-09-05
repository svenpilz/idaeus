SECTIONS {
	/*
	 * Raspberry Pi bootloader executes at 0x8000.
	 * All sections are page aligned.
	 */
	. = 0x8000;
	__kernel_start = .;
	
	
	/*
	 * text
	 */
	__kernel_text_start = .;
	.text : {
		/*
		 * First the bootstrap code.
		 */
		*(.text.bootstrap)
		*(.text)
	}
	. = ALIGN(4096);
	__kernel_text_end = .;
	

	/*
	 * rodata
	 */
	__kernel_rodata_start = .;
	.rodata : {
		*(.rodata)
	}
	. = ALIGN(4096);
	__kernel_rodata_end = .;
	
	
	/*
	 * data
	 */
	__kernel_data_start = .;
	.data : {
		*(.data)
	}
	. = ALIGN(4096);
	__kernel_data_end = .;


	/*
	 * bss
	 */	
	__kernel_bss_start = .;
	.bss : {
		*(.bss)
	}
	. = ALIGN(4096);
	__kernel_bss_end = .;
	__kernel_end = .;
}
