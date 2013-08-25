#include <stdio.h>
#include "driver/bcm2835/uart/uart.h"
#include "driver/bcm2835/framebuffer/framebuffer.h"
#include <assert.h>

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
	intall_interrupt_handler(0x0, interrupt);
	intall_interrupt_handler(0x4, undefined_exception);
	intall_interrupt_handler(0x8, swi);
	intall_interrupt_handler(0xc, interrupt);
	intall_interrupt_handler(0x10, irq);
	intall_interrupt_handler(0x14, fiq);
	
	// FPU test.
	printf("Float: %f\n", -25.85);
	printf("0x%x 0x%X\n", 0xABC, 0xDEF);
	
	puts("swi");
	asm("swi 1");	
	puts("terminate");
}

