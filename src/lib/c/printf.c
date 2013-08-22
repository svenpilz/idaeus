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
