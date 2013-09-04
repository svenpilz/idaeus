#include <kernel/interfaces/platform.h>
#include <stdio.h>

#include "uart.h"
#include "framebuffer.h"

int platform_init() {
	uart_init();
	libc_init_putc(uart_putc);
	bcm2835_framebuffer_init(1024, 768, 24);
	return 0;
}
