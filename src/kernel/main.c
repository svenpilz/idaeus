#include <stdio.h>
#include "driver/bcm2835/uart/uart.h"
#include "driver/bcm2835/framebuffer/framebuffer.h"
#include "interfaces/framebuffer.h"
#include <math.h>

#include <primitives.h>


uint8_t buffer[1024*768*3];
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
	
	printf("[DEBUG] kernel: syscall %u issued.\n", syscall_id);
}
/*
#define INTERRUPT_BASE_ADDRESS 0x2000B000
const uint32_t IRQ_BASIC_PENDING_REGISTER_ADDRESS = INTERRUPT_BASE_ADDRESS + 0x200;
const uint32_t BASE_INTERRUPT_ENABLE_REGISTER_ADDRESS = INTERRUPT_BASE_ADDRESS + 0x218;

#define SYSTEM_TIMER_REGISTER_BASE_ADDRESS 0x20003000
const uint32_t SYSTEM_TIMER_CONTROL_STATUS_REGISTER_ADDRESS = SYSTEM_TIMER_REGISTER_BASE_ADDRESS;
const uint32_t SYSTEM_TIMER_COUNTER_LOW_REGISTER_ADDRESS = SYSTEM_TIMER_REGISTER_BASE_ADDRESS + 0x4;
const uint32_t SYSTEM_TIMER_0_REGISTER_ADDRESS = SYSTEM_TIMER_REGISTER_BASE_ADDRESS + 0xc;
*/
void __attribute__ ((interrupt)) irq(void) {	
	*(uint32_t*)0x20003000 = 2;
	puts("irq-handler");
}

void __attribute__ ((interrupt)) fiq(void) {	
	puts("fiq-handler");
}

void __attribute__ ((interrupt)) interrupt(void) {	
	puts("interrupt-handler");
}

void __attribute__ ((interrupt)) undefined_exception(void) {
	while(1) {}
}

uint32_t arm_fpu_read_fpexc() {
	uint32_t v;
	asm("vmrs %0, fpexc" : "=r" (v));
	return v;
}

void arm_fpu_set_fpexc(uint32_t v) {
	asm("vmsr fpexc, %0" : : "r" (v));
}

const uint32_t ARM_FPU_FPEXC_FLAG_ENABLE = 1 << 30;
void platform_init() {
	arm_fpu_set_fpexc(arm_fpu_read_fpexc() | ARM_FPU_FPEXC_FLAG_ENABLE);
}

void main(void) {
	platform_init();
	uart_init();
	libc_init_putc(uart_putc);
	
	puts("framebuffer init");
	bcm2835_framebuffer_init(1024, 768, 24);
	
	kernel_framebuffer_t fb;
	fb.frame = buffer;
	fb.width = 1024;
	fb.height = 768;
	fb.depth = 24;
	
	
	uint8_t* img = fb.frame;
	
	for (uint32_t row = 0; row < fb.height; row++) {
		for (uint32_t col = 0; col < fb.width; col++) {
			*img++ = 255;
			*img++ = 0;
			*img++ = 0;
		}
	}
	
	bcm2835_framebuffer_draw(&fb);
	
	puts("draw");
	graphics_fb_point(&fb, 10, 10);
	graphics_fb_draw_line(&fb, 15, 15, 160, 100);
	bcm2835_framebuffer_draw(&fb);
	
	puts("swi-setup");
	intall_interrupt_handler(0x0, interrupt);
	intall_interrupt_handler(0x4, undefined_exception);
	intall_interrupt_handler(0x8, swi);
	intall_interrupt_handler(0xc, interrupt);
	intall_interrupt_handler(0x10, irq);
	intall_interrupt_handler(0x14, fiq);
	
	// FPU test.
	printf("Float: %f\n", -25.85);
	//printf("%u, 0x%x 0x%X\n", 123, 0xABC, 0xDEF);
	printf("%f %f\n", sin(0), sin(3.14159/2));
	printf("%f %f\n", sin(3.14159*2), sin(3.14159));
	//printf("Float: %f\n", -25.85);
	
	puts("swi");
	asm("swi 1");	
	puts("terminate");
}

