#include "uart.h"
#include "gpio.h"

/*
 * ## UART Assignment on the GPIO Pin map
   ## (BCM2835 ARM Peripherals, Broadcom)
 * PIN    | Pull | ALT0 | ALT1 | ALT2 | ALT3 | ALT4 | ALT5
 * -------|------|------|------|------|------|------|-----
 * GPIO14 | Low  | TXD0 |      |      |      |      |
 * GPIO15 | Low  | RXD0 |      |      |      |      |
 * GPIO16 | Low  |      |      |      | CTS0 |      |
 * GPIO17 | Low  |      |      |      | RTS0 |      |
 * GPIO30 | Low  |      |      |      | CTS0 |      |
 * GPIO31 | Low  |      |      |      | RTS0 |      |
 * GPIO32 | Low  |      |      |      | TXD0 |      |
 * GPIO33 | Low  |      |      |      | RXD0 |      |
 * GPIO36 | High |      |      | TXD0 |      |      |
 * GPIO37 | Low  |      |      | RXD0 |      |      |
 * GPIO38 | Low  |      |      | RTS0 |      |      |
 * GPIO39 | Low  |      |      | CTS0 |      |      |
 */

#define UART_BASE_ADDRESS 0x20201000
const uint32_t UART_DR_ADDRESS = UART_BASE_ADDRESS;
const uint32_t UART_FR_ADDRESS = UART_BASE_ADDRESS + 0x18;
const uint32_t UART_IBRD_ADDRESS = UART_BASE_ADDRESS + 0x24;
const uint32_t UART_FBRD_ADDRESS = UART_BASE_ADDRESS + 0x28;
const uint32_t UART_LCRH_ADDRESS = UART_BASE_ADDRESS + 0x2C;
const uint32_t UART_CR_ADDRESS = UART_BASE_ADDRESS + 0x30;
const uint32_t UART_IMSC_ADDRESS = UART_BASE_ADDRESS + 0x38;
const uint32_t UART_ICR_ADDRESS = UART_BASE_ADDRESS + 0x44;

uart_cr_t* cr;
uart_dr_t* dr;

void uart_init() {
	cr = (uart_cr_t*)UART_CR_ADDRESS;
	dr = (uart_dr_t*)UART_DR_ADDRESS;
	uint32_t* icr = (uint32_t*)UART_ICR_ADDRESS;
	uint32_t* ibrd = (uint32_t*)UART_IBRD_ADDRESS;
	uint32_t* fbrd = (uint32_t*)UART_FBRD_ADDRESS;
	uint32_t* imsc = (uint32_t*)UART_IMSC_ADDRESS;
	uart_lcrh_t* lcrh = (uart_lcrh_t*)UART_LCRH_ADDRESS;

	cr->uart_enable = 0;

	gpio_init();
	gpio_set_pud((1 << 14) | (1 << 15), GPIO_DISBALE_PULL_UP_DOWN);

	*icr = 0x7FF;
	*ibrd = 1;
	*fbrd = 40;

	lcrh->word_length = UART_8_BITS_WORD;
	lcrh->enable_fifos = 1;

	*imsc =  (1 << 1) | (1 << 4) | (1 << 5) |
		(1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10);

	cr->transmit_enable = 1;
	cr->receive_enable = 1;
	cr->uart_enable = 1;
}

void uart_putc(uint8_t byte) {
	dr->data = byte;
}

