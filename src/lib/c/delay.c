#include <delay.h>

void delay(int32_t count) {
	asm volatile(
		"__delay_%=: subs %[count], %[count], #1\n"
		"bne __delay_%=\n"
	: : [count]"r"(count) : "cc");
}
