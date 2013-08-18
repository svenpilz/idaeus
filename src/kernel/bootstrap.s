.section .text.bootstrap
.global _start
_start:
	mov sp, #0x8000
	bl main
halt:
	wfe
	b halt
