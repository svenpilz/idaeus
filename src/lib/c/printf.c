#include "printf.h"
#include <stdio.h>

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

typedef enum {
	FORMAT_IDENTIFIER_READ,
	ERROR,
	TEXT
} format_status_t;

void print_decimal_uint(unsigned int num) {
	unsigned int quotient = num / 10;
	
	if (quotient != 0) {
		print_decimal_uint(quotient);
		putc(num % 10 + '0');
	} else {
		putc(num + '0');
	}
}

void print_decimal_int(int num) {
	if (num < 0) {
		putc('-');
		num *= -1;
	}
	
	print_decimal_uint(num);
}

/**
 * todo: This is probably the worst way of converting double to string
 *       and was written just as a test for the FPU support of the
 *       compiler. IEEE-754 anybody?
 */
void print_floating_point(double num) {
	print_decimal_int((int)num);
	putc('.');
	
	num -= (int)num;
	if (num < 0) {
		num *= -1;
	}
	while (num > 0) {
		num *= 10;
		putc((int)num + '0');
		num -= (int)num;
	}
}

int printf(const char* format, ...) {
	format_status_t status = TEXT;
	va_list variables;
	va_start(variables, format);
	
	for (; *format != 0; ++format) {
		switch (status) {
			case FORMAT_IDENTIFIER_READ:
				switch (*format) {
					case 'u':
						print_decimal_uint(va_arg(variables, unsigned int));
						status = TEXT;
						break;
					case 'f':
						print_floating_point(va_arg(variables, double));
						status = TEXT;
						break;
					default:
						status = ERROR;
				}
				break;
			case TEXT:
			default:
				if (*format == '%') {
					status = FORMAT_IDENTIFIER_READ;
				} else {
					putc(*format);
				}
		}
	}
	
	va_end(variables);
}
