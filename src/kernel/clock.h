#ifndef KERNEL_CLOCK_H
#define KERNEL_CLOCK_H

typedef void (*kernel_clock_tick_handler_t)();

int kernel_clock_init();
int kernel_clock_add_tick_handler(kernel_clock_tick_handler_t handler);

#endif
