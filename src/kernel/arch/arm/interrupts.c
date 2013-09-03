#include <stdint.h>

#include <kernel/syscall.h>
#include <kernel/error_handler.h>

/*
 * Reset
 */
static void __attribute__ ((interrupt)) reset(void) {
	handle_cpu_error();
}

/*
 * Undefined instruction
 */
static void __attribute__ ((interrupt)) undefined(void) {
	handle_cpu_error();
}


/*
 * Software interrupt
 */
static void __attribute__ ((interrupt ("SWI"))) swi(void) {
	uint32_t syscall_id;
	
	/*
	 * Read “comment” section of SWI instruction, this is
	 * used as the syscall id.
	 */
	asm volatile ("ldr %0, [lr,#-4]" : "=r" (syscall_id));
	syscall_id &= 0x00FFFFFF;
	
	handle_syscall_request(syscall_id);
}

/*
 * prefetch abort
 */
static void __attribute__ ((interrupt)) prefetch_abort(void) {
	handle_cpu_error();
}

/*
 * data abort
 */
static void __attribute__ ((interrupt)) data_abort(void) {
	handle_cpu_error();
}

/*
 * irq
 */
static void __attribute__ ((interrupt)) irq(void) {
	handle_cpu_error();
}

/*
 * fiq
 */
static void __attribute__ ((interrupt)) fiq(void) {
	handle_cpu_error();
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
	intall_interrupt_handler(0x0, reset);
	intall_interrupt_handler(0x4, undefined);
	intall_interrupt_handler(0x8, swi);
	intall_interrupt_handler(0xc, prefetch_abort);
	intall_interrupt_handler(0x10, data_abort);
	intall_interrupt_handler(0x14, irq);
	intall_interrupt_handler(0x18, fiq);
	
	return 0;
}

