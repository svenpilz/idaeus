#include <idaeus/base/string.h>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace idaeus {

String String::fromUTF8(const char* str) {
	assert(str != NULL);
	
	unsigned char next = 0;
	unicode_char sequence;
	String u(strlen(str));
	
	for (; *str != NULL; ++str) {
		if (next == 0) {
			if ((*str & 0x80) == 0x0) { //0xxxxxxx
				next = 0;
				sequence = *str;
			} else if ((*str & 0xE0) == 0xC0) { //110xxxxx
				next = 1;
				sequence = (*str++ & 0x1F) << 6;
			} else if ((*str & 0xF0) == 0xE0) { //1110xxxx
				next = 2;
				sequence = (*str++ & 0xF) << 12;		
			} else if ((*str & 0xF8) == 0xF0) { //11110xxx
				next = 3;
				sequence = (*str++ & 0x7) << 18;
			} else if ((*str & 0xFC) == 0xF8) { //111110xx
				next = 4;
				sequence = (*str++ & 0x3) << 24;
			} else if ((*str & 0xFE) == 0xFC) { //1111110x
				next = 5;
				sequence = (*str++ & 0x1) << 30;
			} else {		
				printf("(error 1: %s 0x%hhx) ", str, *str);
			}
		}
		
		if (next > 0) {			
			next--;
			if ((*str & 0xC0) == 0x80) {
				sequence |= (*str & 0x3F) << next*6;
			} else {
				printf("(error 2: %s 0x%hhx n=%d) ", str, *str, next);
			}
		}
		
		if (next == 0) {
			u.append(sequence);
		}
	}
	
	if (next != 0) {
		puts("unexpected end of string");
	}
	
	return u;
}
		
String::String(size_t len) : data(NULL), datalen(0), stringlen(0) {
	adjustSize(len);
}

String::~String() {
	printf("String::~String: free 0x%x ", data);
	assert(data != NULL);
	free(data);
	data = NULL;	
}

void String::adjustSize(size_t len) {
	if (stringlen < len) {
		data = (unicode_char*)realloc(data, sizeof(unicode_char)*len);
		assert(data != NULL);
		datalen = len;
	}
}

void String::append(unicode_char c) {
	adjustSize(stringlen + 1);
	data[stringlen++] = c;
}
		
unicode_char& String::operator[](size_t i) {
	assert(i < stringlen);
	return data[i];
}

size_t String::length() const {
	return stringlen;
}

}
