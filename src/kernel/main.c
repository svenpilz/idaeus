#include <stdio.h>
#include "driver/bcm2835/uart/uart.h"

void main(void) {
	uart_init();
	libc_init_putc(uart_putc);
	puts("Hello World!");
}
