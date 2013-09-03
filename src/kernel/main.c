#include <stdio.h>
#include "platform/bcm2835/framebuffer.h"
#include <kernel/interfaces/arch.h>
#include <kernel/interfaces/platform.h>
#include <kernel/interfaces/framebuffer.h>
#include <math.h>

#include <graphics/primitives.h>

uint8_t buffer[1024*768*3];

void main(uint32_t unused, uint32_t arm_linux_machine_type, uint32_t atag) {
	arch_init();
	platform_init();
	
	printf("bootloader information: arm_linux_machine_type=0x%x, atag=0x%x\n",
		arm_linux_machine_type, atag);
	
	kernel_framebuffer_t fb;
	fb.frame = buffer;
	fb.width = 1024;
	fb.height = 768;
	fb.depth = 24;
	
	puts("render");
	graphics_fb_fill_rectangle(&fb, GRAPHICS_COLOR_RED, 0, 0, fb.width-1, fb.height-1);
	graphics_fb_draw_point(&fb, GRAPHICS_COLOR_GREEN, 10, 10);
	graphics_fb_draw_line(&fb, graphics_color_set_blue(GRAPHICS_COLOR_GREEN, 255), 15, 15, 160, 100);
	
	puts("draw");
	bcm2835_framebuffer_draw(&fb);
	
	puts("swi");
	asm("swi 1");	
	puts("terminate");
}

