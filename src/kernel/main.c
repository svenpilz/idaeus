#include <stdio.h>
#include "platform/bcm2835/framebuffer.h"
#include <kernel/interfaces/arch.h>
#include <kernel/interfaces/timer.h>
#include <kernel/interfaces/platform.h>
#include <kernel/interfaces/framebuffer.h>

#include <math.h>

#include <graphics/primitives.h>

#include "clock.h"
#include "memory.h"

uint8_t buffer[1024*768*3];

platform_information_t platform_information;

void main(uint32_t unused, uint32_t arm_linux_machine_type, uint32_t atag) {
	arch_init();
	platform_init(atag, &platform_information);
	
	kernel_memory_init(&platform_information);
	kernel_clock_init();
	
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

