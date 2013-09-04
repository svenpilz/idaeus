#include "timer.h"
#include "../../arch/arm/interrupts.h"

#include <kernel/interfaces/timer.h>

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/**
 * @file
 * @todo Right now only the second timer works. But why?
 */

#define NUMBER_OF_TIMERS 4
#define BCM2835_TIMER_BASE_REGISTER_ADDRESS 0x20003000
const uint32_t BCM2835_TIMER_CONTROL_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS;
const uint32_t BCM2835_TIMER_COUNTER_LOW_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS + 0x4;
const uint32_t BCM2835_TIMER_COUNTER_HIGH_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS + 0x8;
const uint32_t BCM2835_TIMER_0_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS + 0xc;
const uint32_t BCM2835_TIMER_1_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS + 0x10;
const uint32_t BCM2835_TIMER_2_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS + 0x14;
const uint32_t BCM2835_TIMER_3_REGISTER_ADDRESS = BCM2835_TIMER_BASE_REGISTER_ADDRESS + 0x18;

#define CONTROL_REGISTER (*(uint32_t*)BCM2835_TIMER_CONTROL_REGISTER_ADDRESS)
#define COUNTER_LOW_REGISTER (*(uint32_t*)BCM2835_TIMER_COUNTER_LOW_REGISTER_ADDRESS)
#define COUNTER_HIGH_REGISTER (*(uint32_t*)BCM2835_TIMER_COUNTER_HIGH_REGISTER_ADDRESS)
#define TIMER_REGISTER(i) (*(uint32_t*)(BCM2835_TIMER_0_REGISTER_ADDRESS + i*0x4))

static timer_event_handler_t event_handler[NUMBER_OF_TIMERS];

void print_register() {
	printf("bcm2835 timer: cs=0x%x, clo=0x%x, chi=0x%x, c0=0x%x, c1=0x%x, c2=0x%x, c3=0x%x\n",
		CONTROL_REGISTER, COUNTER_LOW_REGISTER, COUNTER_HIGH_REGISTER,
		TIMER_REGISTER(0), TIMER_REGISTER(1), TIMER_REGISTER(2),
		TIMER_REGISTER(3));
}

void print_int_register() {
	printf("basic_pending=0x%x, irq1_pending=0x%x, irq2_pending=0x%x, fiq_control=0x%x, irq1_enable=0x%x, irq2_enable=0x%x, basic_irq_enable=0x%x\n",
		*((uint32_t*)(0x2000B000 + 0x200)), 
		*((uint32_t*)(0x2000B000 + 0x204)),
		*((uint32_t*)(0x2000B000 + 0x208)),
		*((uint32_t*)(0x2000B000 + 0x20c)),
		*((uint32_t*)(0x2000B000 + 0x210)),
		*((uint32_t*)(0x2000B000 + 0x214)),
		*((uint32_t*)(0x2000B000 + 0x218))
		);
}

void timer() {
	for (uint i = 0; i < NUMBER_OF_TIMERS; ++i) {
		if (CONTROL_REGISTER & 1 << i) {
			CONTROL_REGISTER = 1 << i;
			if (event_handler[i] != NULL) {
				event_handler[i]();
			}
		}
	}
}

int timer_init() {
	for (uint i = 0; i < NUMBER_OF_TIMERS; ++i) {
		event_handler[i] = NULL;
	}

	/*
	 * use fiq
	 */
	*((uint32_t*)0x2000B210) = 0x00000000;
    	*((uint32_t*)0x2000B20C) = 0x81;
    	
    	CONTROL_REGISTER = 1;
    	CONTROL_REGISTER = 1 << 2;
    	CONTROL_REGISTER = 1 << 3;
    	CONTROL_REGISTER = 1 << 4;
}

uint timer_number_of_channels() {
	return NUMBER_OF_TIMERS;
}

uint timer_current_counter() {
	return COUNTER_LOW_REGISTER;
}

uint timer_channel_comperator(uint channel) {
	assert(channel < NUMBER_OF_TIMERS);
	return TIMER_REGISTER(channel);
}

int timer_channel_set_comperator(uint channel, uint value) {
	if (channel >= NUMBER_OF_TIMERS) {
		return -1;
	}
	
	TIMER_REGISTER(channel) = value;
	
	return 0;
}

int timer_channel_set_event_handler(uint channel, timer_event_handler_t handler) {
	if (channel >= NUMBER_OF_TIMERS) {
		return -1;
	}
	
	event_handler[channel] = handler;
	CONTROL_REGISTER = 1 << channel;
	arm_enable_fiq();
	
	return 0;
}

