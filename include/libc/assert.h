#ifndef INCLUDE_LIBC_ASSERT_H
#define INCLUDE_LIBC_ASSERT_H

#include "stdio.h"

#define assert(expression) if (!(expression)) { \
	printf("[DEBUG] Assertion \"%s\" failed in %s:%u!\n", #expression, __FILE__, __LINE__); \
}

#endif
