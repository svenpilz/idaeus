#ifndef KERNEL_DRIVER_BCM2835_UART_UART_H
#define KERNEL_DRIVER_BCM2835_UART_UART_H

#include <stdint.h>

typedef struct {
	uint8_t data;
	unsigned char framing_error : 1;
	unsigned char parity_error : 1;
	unsigned char break_error : 1;
	unsigned char overrun_error : 1;
	unsigned int reserved : 20;
} __attribute__((packed)) uart_dr_t;

typedef struct {
	unsigned char uart_enable : 1;
	unsigned char siren : 1;
	unsigned char sirlp : 1;
	unsigned char reserved0 : 4;
	unsigned char loopback_enable : 1;
	unsigned char transmit_enable : 1;
	unsigned char receive_enable : 1;
	unsigned char dtr : 1;
	unsigned char request_to_send : 1;
	unsigned char out1 : 1;
	unsigned char out2 : 1;
	unsigned char rts_enable : 1;
	unsigned char cts_enable : 1;
	unsigned int reserved1 : 16;
} __attribute__((packed)) uart_cr_t;

typedef enum {
	UART_5_BITS_WORD = 0,
	UART_6_BITS_WORD = 1,
	UART_7_BITS_WORD = 2,
	UART_8_BITS_WORD = 3,
} uart_word_length_t;

typedef struct {
	unsigned char send_break : 1;
	unsigned char parity_enable : 1;
	unsigned char even_parity : 1;
	unsigned char two_stop_bits : 1;
	unsigned char enable_fifos : 1;
	unsigned char word_length : 2;
	unsigned char stick_parity : 1;
	unsigned int reserved : 24;
	
} __attribute__((packed)) uart_lcrh_t;

void uart_init();
void uart_putc(uint8_t c);

#endif
