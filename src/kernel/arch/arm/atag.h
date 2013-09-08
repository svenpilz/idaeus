#ifndef KERNEL_ARCH_ARM_ATAG_H
#define KERNEL_ARCH_ARM_ATAG_H

/**
 * See http://www.simtec.co.uk/products/SWLINUX/files/booting_article.html
 */

typedef enum {
	ARM_ATAG_TYPE_NONE = 0,
	ARM_ATAG_TYPE_CORE = 0x54410001,
	ARM_ATAG_TYPE_MEM = 0x54410002
} arm_atag_type_t;

typedef struct {
	uint32_t size;
	uint32_t type;
} arm_atag_header_t;

typedef struct {
	uint32_t flags;
	uint32_t page_size;
	uint32_t root_device;
} arm_atag_core_t;

typedef struct {
	uint32_t size;
	uint32_t start;
} arm_atag_mem_t;

typedef struct {
	arm_atag_header_t header;
	union {
		arm_atag_core_t core;
		arm_atag_mem_t mem;
	};
} arm_atag_list_t;

#endif
