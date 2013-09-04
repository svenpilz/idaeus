.section .text.bootstrap
.global _start
_start:
	@
	@ set the stack for FIQ mode
	@
	mov r4, #0xD1   @ fiq mode with no interrupts
	msr cpsr_c,r4
	mov sp, #0x4000

	@
	@ set the stack for supervisor mode
	@
	mov r4, #0xD3   @ supervisor mode with no interrupts
	msr cpsr_c, r4
	mov sp, #0x8000

	@
	@ jump to kernel main
	@
	bl main

halt:
	wfe
	b halt

