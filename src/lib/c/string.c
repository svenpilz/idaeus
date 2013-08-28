#include <string.h>

void* memchr(void* string, unsigned char value, size_t length) {
	for (; length > 0; --length) {
		if (*(unsigned char*)string == value) {
			return string;
		}
		
		++string;
	}
	
	return NULL;
}

int memcmp(const void* s1, const void* s2, size_t num) {
	for (; num > 0; --num) {
		if (*(const char*)s1 > *(const char*)s2) {
			return 1;
		} else if (*(const char*)s1 < *(const char*)s2) {
			return -1;
		}
		
		++s1;
		++s2;
	}
	
	return 0;
}

void* memcpy(void* destination, const void* source, size_t num) {
	if (destination < source) {
		for (size_t i = 0; i < num; ++i) {
			((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
		}
	} else {
		for (; num > 0; --num) {
			((unsigned char*)destination)[num-1] = ((unsigned char*)source)[num-1];
		}
	}
	
	return destination;
}

void* memmove(void* destination, const void* source, size_t num) {
	/*
	 * memcpy already handles possible overlapping of destination and source
	 */
	return memcpy(destination, source, num);
}

void* memset(void* destination, unsigned char value, size_t num) {
	for (; num > 0; --num) {
		*(unsigned char*)destination++ = value;
	}
	
	return destination;
}

char* strcat(char* destination, const char* source) {
	const size_t destlen = strlen(destination);
	memcpy(destination+destlen, source, strlen(source));
	return destination;
}

char* strchr(char* str, unsigned char value) {
	return memchr(str, value, strlen(str));
}


int strcmp(const char* s1, const char* s2) {
	const size_t s1_len = strlen(s1);
	const size_t s2_len = strlen(s2);
	
	if (s1_len > s2_len) {
		return 1;
	} else if (s1_len < s2_len) {
		return -1;
	} else {
		return memcmp(s1, s2, s1_len);
	}
}

char* strcpy(char* destination, const char* source) {
	return memcpy(destination, source, strlen(source) + 1);
}

size_t strspn(const char* str, const char* chars) {
	const size_t clen = strlen(chars);
	size_t i;
	
	for (i = 0; str[i] != 0; ++i) {
		for (size_t c = 0; c < clen; ++c) {
			if (str[i] == chars[c]) {
				return i;
			}
		}
	}
	
	return i;
}

size_t strlen(const char* str) {
	size_t length;
	for (length = 0; *str; ++str);
	return length;
}

