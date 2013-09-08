#include <stdio.h>
#include "platform/bcm2835/framebuffer.h"
#include <kernel/interfaces/arch.h>
#include <kernel/interfaces/platform.h>
#include <kernel/interfaces/framebuffer.h>

#include <math.h>

#include <graphics/primitives.h>

#include "clock.h"

uint8_t buffer[1024*768*3];

extern void __kernel_start;
extern void __kernel_end;
extern void __kernel_text_start;
extern void __kernel_text_end;
extern void __kernel_rodata_start;
extern void __kernel_rodata_end;
extern void __kernel_data_start;
extern void __kernel_data_end;
extern void __kernel_bss_start;
extern void __kernel_bss_end;

platform_information_t platform_information;

void main(uint32_t unused, uint32_t arm_linux_machine_type, uint32_t atag) {
	arch_init();
	platform_init(atag, &platform_information);
	
	printf("kernel platform: memory=%u bytes, page_size=%u bytes.\n", platform_information.memory_size, platform_information.memory_page_size);
	
	kernel_clock_init();
	
	printf("kernel layout: text=0x%x - 0x%x (%u bytes), rodata=0x%x - 0x%x (%u bytes),\n"
		"               data=0x%x - 0x%x (%u bytes), bss=0x%x - 0x%x (%u bytes),\n"
		"               total size=%u bytes.\n",
		&__kernel_text_start, &__kernel_text_end, &__kernel_text_end - &__kernel_text_start,
		&__kernel_rodata_start, &__kernel_rodata_end, &__kernel_rodata_end - &__kernel_rodata_start,
		&__kernel_data_start, &__kernel_data_end, &__kernel_data_end - &__kernel_data_start,
		&__kernel_bss_start, &__kernel_bss_end, &__kernel_bss_end - &__kernel_bss_start,
		&__kernel_end - &__kernel_start);
	
	printf("bootloader information: arm_linux_machine_type=0x%x, atag=0x%x.\n",
		arm_linux_machine_type, atag);
	
	kernel_framebuffer_t fb;
	fb.frame = buffer;
	fb.width = 1024;
	fb.height = 768;
	fb.depth = 24;
	
	graphics_fb_fill_rectangle(&fb, GRAPHICS_COLOR_RED, 0, 0, fb.width-1, fb.height-1);
	graphics_fb_draw_point(&fb, GRAPHICS_COLOR_GREEN, 10, 10);
	graphics_fb_draw_line(&fb, graphics_color_set_blue(GRAPHICS_COLOR_GREEN, 255), 15, 15, 160, 100);
	
	bcm2835_framebuffer_draw(&fb);

	printf("kernel: initialization complete, took %u msec.\n", timer_current_counter()/1000);
}

