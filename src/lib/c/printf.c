#include "printf.h"
#include <stdio.h>
#include <assert.h>

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

const char* digits_lower_case = "0123456789abcdef";
const char* digits_upper_case = "0123456789ABCDEF";


void print_uint(unsigned int num, uint8_t base, const char* digits) {
	unsigned int quotient = num / base;
	
	if (quotient != 0) {
		print_uint(quotient, base, digits);
		putc(digits[num % base]);
	} else {
		putc(digits[num]);
	}
}

void print_int(int num, uint8_t base, const char* digits) {
	if (num < 0) {
		putc('-');
		num *= -1;
	}
	
	print_uint(num, base, digits);
}

/**
 * todo: This is probably the worst way of converting double to string
 *       and was written just as a test for the FPU support of the
 *       compiler. IEEE-754 anybody?
 */
void print_floating_point(double num, uint8_t base, const char* digits) {
	print_int((int)num, base, digits);
	putc('.');
	
	num -= (int)num;
	if (num < 0) {
		num *= -1;
	}
	while (num > 0) {
		num *= 10;
		putc(digits[(int)num]); 
		num -= (int)num;
	}
}

void print_string(const char* str) {
	while(*str) {
		putc(*str++);
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
					case 'd':
					case 'i':
						print_int(va_arg(variables, int), 10, digits_lower_case);
						break;
					case 'u':
						print_uint(va_arg(variables, unsigned int), 10, digits_lower_case);
						break;
					case 'x':
						print_uint(va_arg(variables, unsigned int), 16, digits_lower_case);
						break;
					case 'X':
						print_uint(va_arg(variables, unsigned int), 16, digits_upper_case);
						break;
					case 'f':
						print_floating_point(va_arg(variables, double), 10, digits_lower_case);
						break;
					case 's':
						print_string(va_arg(variables, const char*));
						break;
					default:
						status = ERROR;
						continue;
				}
				status = TEXT;
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
