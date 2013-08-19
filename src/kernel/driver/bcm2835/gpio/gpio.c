#include "gpio.h"

#include <delay.h>

#define GPIO_BASE_ADDRESS 0x20200000
const uint32_t GPIO_GPPUD_ADDRESS = GPIO_BASE_ADDRESS + 0x94;
const uint32_t GPIO_GPPUDCLK0_ADDRESS = GPIO_BASE_ADDRESS + 0x98;
const uint32_t GPIO_GPPUDCLK1_ADDRESS = GPIO_BASE_ADDRESS + 0x9C;

uint32_t* gppud;
uint32_t* gppudclk0;
uint32_t* gppudclk1;

void gpio_init() {
	gppud = (uint32_t*)GPIO_GPPUD_ADDRESS;
	gppudclk0 = (uint32_t*)GPIO_GPPUDCLK0_ADDRESS;
	gppudclk1 = (uint32_t*)GPIO_GPPUDCLK1_ADDRESS;
}

void gpio_set_pud(uint64_t pins, gpio_pud_state_t state) {
	*gppud = (*gppud & 0xFFFFFFFC) | state;
	delay(150);
	*gppudclk0 = pins & 0x000000FFFFFFFF;
	*gppudclk1 = (*gppudclk1 & 0xFFC00000) | (pins & 0x003FFFFF00000000 >> 32);
	delay(150);
	*gppudclk0 = 0;
	*gppudclk1 = *gppudclk1 & 0xFFC00000;
}
