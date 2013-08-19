#include "puts.h"
#include "putc.h"

void puts(const char* s) {
	while(*s != 0) {
		putc(*s++);
	}
	
	putc('\n');
}
