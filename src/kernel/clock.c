#include "clock.h"

#include <kernel/interfaces/timer.h>
#include <stdio.h>

#define TIMER_TICK 1000*1000
#define TIMER 1

static timer_handler() {
	timer_channel_set_comperator(TIMER, timer_current_counter() + TIMER_TICK);
}

int kernel_clock_init() {
	timer_channel_set_comperator(TIMER, timer_current_counter() + TIMER_TICK);
	timer_channel_set_event_handler(TIMER, timer_handler);
	
	printf("kernel clock: using timer %u, ticking every %u microseconds.\n", TIMER, TIMER_TICK);
}
