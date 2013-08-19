#include <stdio.h>
#include "driver/bcm2835/uart/uart.h"
#include "driver/bcm2835/framebuffer/framebuffer.h"



void main(void) {
	uart_init();
	libc_init_putc(uart_putc);
	puts("framebuffer init");
	frame_buffer_info_t frame_buffer_info;
	framebuffer_init(&frame_buffer_info, 1024, 768, 16);
	puts("draw");
	
	uint16_t* img = frame_buffer_info.gpu_pointer;
	uint16_t color = 0;
	
	for (uint32_t x = 0; x < frame_buffer_info.physical_width; x++) {
		for (uint32_t y = 0; y < frame_buffer_info.physical_height; y++) {
			*img = color++;
			img += 2;
		}
	}
	
	puts("terminate");
}
