#ifndef INCLUDE_KERNEL_INTERFACES_INTERRUPTS_H
#define INCLUDE_KERNEL_INTERFACES_INTERRUPTS_H

#include "arch.h"

arch_register_set_t* arch_int_get_saved_register();
int arch_int_set_saved_register(arch_register_set_t* set);

#endif
