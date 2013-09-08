#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <kernel/interfaces/platform.h>

extern unsigned int __kernel_start;
extern unsigned int __kernel_end;
extern unsigned int __kernel_text_start;
extern unsigned int __kernel_text_end;
extern unsigned int __kernel_rodata_start;
extern unsigned int __kernel_rodata_end;
extern unsigned int __kernel_data_start;
extern unsigned int __kernel_data_end;
extern unsigned int __kernel_bss_start;
extern unsigned int __kernel_bss_end;

int kernel_memory_init(platform_information_t* platform_information);

#endif
