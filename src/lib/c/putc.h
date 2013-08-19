#ifndef LIB_C_PUTC_H
#define LIB_C_PUTC_H

#include <stdint.h>

typedef void (*libc_putc_t)(uint8_t);
void libc_init_putc(libc_putc_t f);
extern libc_putc_t putc;

#endif
