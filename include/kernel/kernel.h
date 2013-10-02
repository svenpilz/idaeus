#ifndef INCLUDE_KERNEL_KERNEL_H
#define INCLUDE_KERNEL_KERNEL_H

#include "interfaces/arch.h"

arch_register_set_t* kernel_handle_interrupt(arch_register_set_t* register_set);

#endif
