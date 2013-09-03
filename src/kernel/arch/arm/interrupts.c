#include <stdint.h>

void __attribute__ ((interrupt ("SWI"))) swi(void) {
	uint32_t syscall_id;
	
	/*
	 * Read “comment” section of SWI instruction, this is
	 * used as the syscall id.
	 */
	asm volatile ("ldr %0, [lr,#-4]" : "=r" (syscall_id));
	syscall_id &= 0x00FFFFFF;
}

void __attribute__ ((interrupt)) irq(void) {	
	*(uint32_t*)0x20003000 = 2;
}

void __attribute__ ((interrupt)) fiq(void) {	

}

void __attribute__ ((interrupt)) interrupt(void) {	

}

void __attribute__ ((interrupt)) undefined_exception(void) {
	while(1) {}
}

void intall_interrupt_handler(uint32_t interrupt, void* handler) {
	/*
	 * Opcode: 0xEA (Branch, no link, always) and
	 *         relative branch address.
	 */
	handler = (void*)(((uint32_t)handler - interrupt - 8) >> 2);
	*((uint32_t*)interrupt) = 0xEA000000 + (uint32_t)handler;
}

int arm_install_interrupt_handler() {
	intall_interrupt_handler(0x0, interrupt);
	intall_interrupt_handler(0x4, undefined_exception);
	intall_interrupt_handler(0x8, swi);
	intall_interrupt_handler(0xc, interrupt);
	intall_interrupt_handler(0x10, irq);
	intall_interrupt_handler(0x14, fiq);
	
	return 0;
}

