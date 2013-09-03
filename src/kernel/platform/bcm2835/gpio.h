#ifndef KERNEL_PLATFORM_BCM2835_GPIO_H
#define KERNEL_PLATFORM_BCM2835_GPIO_H

#include <stdint.h>

typedef enum {
	GPIO_DISBALE_PULL_UP_DOWN = 0,
	GPIO_ENABLE_PULL_DOWN_CONTROL = 1,
	GPIO_ENABLE_PULL_UP_CONTROL = 2,
	GPIO_PUD_STATE_RESERVED = 3
} gpio_pud_state_t;

void gpio_init();
void gpio_set_pud(uint64_t pins, gpio_pud_state_t state);

#endif
