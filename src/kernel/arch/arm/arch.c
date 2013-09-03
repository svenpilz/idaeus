#include <kernel/interfaces/arch.h>
#include "interrupts.h"
#include "vfp.h"

int arch_init() {
	arm_vfp_init();
	arm_install_interrupt_handler();
}
