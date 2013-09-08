#ifndef INCLUDE_KERNEL_INTERFACES_PLATFORM_h
#define INCLUDE_KERNEL_INTERFACES_PLATFORM_h

#include <stdint.h>

typedef struct {
	uint32_t memory_page_size;
	uint32_t memory_offset;
	uint32_t memory_size;
	uint32_t boot_root_device;
} platform_information_t;

int platform_init(uint32_t atag, platform_information_t* platform_information);

#endif
