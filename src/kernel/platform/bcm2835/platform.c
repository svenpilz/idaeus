#include <kernel/interfaces/platform.h>
#include <stdio.h>

#include "uart.h"
#include "framebuffer.h"
#include "timer.h"

#include "../../arch/arm/atag.h"

void parse_atag(uint32_t atag, platform_information_t* platform_info) {
	arm_atag_list_t* tag = (arm_atag_list_t*)atag;
	
	printf("bcm2835 atag: parse at 0x%x.\n", atag);
	
	do {
		switch (tag->header.type) {
			case ARM_ATAG_TYPE_CORE:
				platform_info->memory_page_size = tag->core.page_size;
				platform_info->boot_root_device = tag->core.root_device;
				
				printf("bcm2835 atag: core.flags=0x%x, core.page_size=%u, core.root_device=%u.\n",
					tag->core.flags, tag->core.page_size, tag->core.root_device);
				break;
				
			case ARM_ATAG_TYPE_MEM:
				platform_info->memory_size = tag->mem.size;
				platform_info->memory_offset = tag->mem.start;
				
				printf("bcm2835 atag: mem.size=%u, mem.start=0x%x.\n",
					tag->mem.size, tag->mem.start);
				break;
				
			default:
				printf("[ERROR] bcm2835 platform: unknown atag type 0x%x!\n", tag->header.type);
		}
		tag = (arm_atag_list_t*)((uint32_t*)tag + tag->header.size);
	} while (tag->header.type != ARM_ATAG_TYPE_NONE);
}

int platform_init(uint32_t atag, platform_information_t* platform_info) {
	uart_init();
	libc_init_putc(uart_putc);
	
	parse_atag(atag, platform_info);
	
	timer_init();
	bcm2835_framebuffer_init(1024, 768, 24);
	
	return 0;
}

