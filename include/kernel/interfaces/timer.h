#ifndef INCLUDE_KERNEL_INTERFACES_TIMER_H
#define INCLUDE_KERNEL_INTERFACES_TIMER_H

#include <stdint.h>

typedef void (*timer_event_handler_t)();

int timer_init();
uint timer_number_of_channels();
uint timer_current_counter();
uint timer_channel_comperator(uint channel);
int timer_channel_set_comperator(uint channel, uint value);
int timer_channel_set_event_handler(uint channel, timer_event_handler_t handler);

#endif
