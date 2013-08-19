#include "putc.h"

libc_putc_t putc;

void libc_init_putc(libc_putc_t f) {
	putc = f;
}
