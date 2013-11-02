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
#include "scheduler.h"

platform_information_t platform_information;

void foo() {
	
	while(1) {printf("new thread says hello!\n");}
}

arch_register_set_t* kernel_handle_interrupt(arch_register_set_t* register_set) {
	kernel_schedule_threads();
	
	//register_set->r[15] = foo;
	
	printf("kernel_handle_interrupt\n");
	
	return register_set;
}

extern unsigned char _font;
kernel_framebuffer_t fb;
uint32_t fbrow;
uint32_t fbcol;
void framebuffer_putc(uint8_t c) {
	if (c == '\n') {
		fbrow++;
		fbcol = 0;
	} else {
		unsigned char *font = &_font;
		font += (c - 0x20) * 16;
	
		for (int row = 0; row < 16; ++row) {
			for (int pixel = 0; pixel < 8; ++pixel) {
				if ((*font & (1 << pixel)) != 0) {
				graphics_fb_draw_point(&fb, GRAPHICS_COLOR_WHITE, 8 - pixel + fbcol*10, row + fbrow*18);
				}
			}
		
			++font;
		}
	
		++fbcol;
	
		if (fbcol > 100) {
			fbrow++;
			fbcol = 0;
		}
	}
	
	if (fbrow > 40) {
		graphics_fb_fill_rectangle(&fb, GRAPHICS_COLOR_BLACK, 0, 0, fb.width-1, fb.height-1);
		fbcol = 0;
		fbrow = 0;
	}
}



void main(uint32_t unused, uint32_t arm_linux_machine_type, uint32_t atag) {
	arch_init();
	platform_init(atag, &platform_information);
	
	fb.frame = (uint8_t*)bcm2835_framebuffer_gpu_pointer();
	fb.width = 1024;
	fb.height = 768;
	fb.depth = 24;
	graphics_fb_fill_rectangle(&fb, GRAPHICS_COLOR_BLACK, 0, 0, fb.width-1, fb.height-1);
	
	fbcol = 0;
	fbrow = 0;
	
	libc_init_putc(framebuffer_putc);
	
	kernel_memory_init(&platform_information);
	kernel_clock_init();
	
	printf("bootloader information: arm_linux_machine_type=0x%x, atag=0x%x.\n",
		arm_linux_machine_type, atag);

	printf("kernel: initialization complete, took %u msec.\n", timer_current_counter()/1000);
}

