#ifndef KERNEL_ARCH_ARM_ARCH_H
#define KERNEL_ARCH_ARM_ARCH_H

typedef struct {
	uint64_t d[16]; // vfp
	uint32_t cpsr;
	uint32_t r[16]; // general purpose	
} __attribute__ ((__packed__)) arch_register_set_t;

#endif
