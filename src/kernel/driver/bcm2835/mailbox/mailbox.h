#ifndef KERNEL_DRIVER_BCM2835_MAILBOX_MAILBOX_H
#define KERNEL_DRIVER_BCM2835_MAILBOX_MAILBOX_H

#include <stdint.h>

void mailbox_write(uint8_t mailbox, void* mail);
int mailbox_read(uint8_t mailbox, uint32_t* mail);

#endif
