#include <stdint.h>
#include <stdio.h>

#include <kernel/syscall.h>
#include <kernel/error_handler.h>
#include <kernel/interfaces/interrupts.h>

arch_register_set_t* arm_interrupt_saved_register_set;

extern void arm_interrupt_entry_reset();
extern void arm_interrupt_entry_undefined();
extern void arm_interrupt_entry_swi();
extern void arm_interrupt_entry_prefetch_abort();
extern void arm_interrupt_entry_data_abort();
extern void arm_interrupt_entry_unused();
extern void arm_interrupt_entry_irq();
extern void arm_interrupt_entry_fiq();

typedef enum {
	ARM_INTERRUPT_RESET = 0,
	ARM_INTERRUPT_UNDEFINED = 1,
	ARM_INTERRUPT_SWI = 2,
	ARM_INTERRUPT_PREFETCH_ABORT = 3,
	ARM_INTERRUPT_DATA_ABORT = 4,
	ARM_INTERRUPT_UNUSED = 5,
	ARM_INTERRUPT_IRQ = 6,
	ARM_INTERRUPT_FIQ = 7
} arm_interrupt_type_t;

arch_register_set_t* arm_handle_interrupt(arm_interrupt_type_t interrupt, arch_register_set_t* register_set) {
	uint32_t syscall_id;
	
	arm_interrupt_saved_register_set = register_set;
	
	switch (interrupt) {
		case ARM_INTERRUPT_RESET:
		case ARM_INTERRUPT_UNDEFINED:
			handle_cpu_error();
			break;
		case ARM_INTERRUPT_SWI:
			asm volatile ("ldr %0, [lr,#-4]" : "=r" (syscall_id));
			syscall_id &= 0x00FFFFFF;
			handle_syscall_request(syscall_id);
			break;
		case ARM_INTERRUPT_PREFETCH_ABORT:
		case ARM_INTERRUPT_DATA_ABORT:
		case ARM_INTERRUPT_UNUSED:
		case ARM_INTERRUPT_IRQ:
			handle_cpu_error();
			break;
		case ARM_INTERRUPT_FIQ:
			timer();
			break;
		default:
			handle_cpu_error();
	}
	
	return arm_interrupt_saved_register_set;
}

static void install_entry(uint32_t interrupt, void* handler) {
	/*
	 * Opcode: 0xEA (Branch, no link, always) and
	 *         relative branch address.
	 */
	handler = (void*)(((uint32_t)handler - interrupt - 8) >> 2);
	*((uint32_t*)interrupt) = 0xEA000000 + (uint32_t)handler;
}


int arm_install_interrupt_handler() {
	install_entry(0x0, arm_interrupt_entry_reset);
	install_entry(0x4, arm_interrupt_entry_undefined);
	install_entry(0x8, arm_interrupt_entry_swi);
	install_entry(0xc, arm_interrupt_entry_prefetch_abort);
	install_entry(0x10, arm_interrupt_entry_data_abort);
	install_entry(0x14, arm_interrupt_entry_unused);
	install_entry(0x18, arm_interrupt_entry_irq);
	install_entry(0x1c, arm_interrupt_entry_fiq);
	
	return 0;
}

void arm_enable_fiq() {
	asm volatile ("mrs r0,cpsr;"
                      "bic r0,#0x40;"
                      "msr cpsr_ctl,r0" ::: "r0");
}

