#include <stdio.h>
#include "driver/bcm2835/uart/uart.h"
#include "driver/bcm2835/framebuffer/framebuffer.h"

void intall_interrupt_handler(uint8_t interrupt, void* handler) {
	/*
	 * Opcode: 0xEA (Branch, no link, always) and
	 *         relative branch address.
	 */
	handler = ((int32_t)handler - interrupt - 8) >> 2;
	*((uint32_t*)interrupt) = 0xEA000000 + handler;
}

void __attribute__ ((interrupt ("SWI"))) swi(void) {
	uint32_t syscall_id;
	
	/*
	 * Read “comment” section of SWI instruction, this is
	 * used as the syscall id.
	 */
	asm volatile ("ldr %0, [lr,#-4]" : "=r" (syscall_id));
	syscall_id &= 0x00FFFFFF;
	
	puts("swi-handler");
}

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
	
	puts("swi-setup");
	intall_interrupt_handler(0x8, swi);
	
	
	puts("swi");
	asm("swi 1");
	
	puts("terminate");
}

