#ifndef INCLUDE_LIBC_STRING_H
#define INCLUDE_LIBC_STRING_H

#include <stdint.h>
#include <stddef.h>

void* memchr(void* string, unsigned char value, size_t length);
int memcmp(const void* s1, const void* s2, size_t num);
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* destination, const void* source, size_t num);
void* memset(void* destination, unsigned char value, size_t num);

char* strcat(char* destination, const char* source);
char* strchr(char* str, unsigned char value);
int strcmp(const char* s1, const char* s2);
char* strcpy(char* destination, const char* source);
size_t strspn(const char* str, const char* chars);
size_t strlen(const char* str);

#endif
