#include <idaeus/unicode.h>
#include <cassert>
#include <cstring>

namespace idaeus {

unicode unicode::fromUTF8(const char* str) {
	assert(str != NULL);
	size_t len = strlen(str);
	
	unicode u(len);
	for (size_t i = 0; i < len; ++i) {
		u[i] = *str++;
	}
	
	return u;
}
		
unicode::unicode(size_t len) {

}

unicode::~unicode() {

}
		
unicode_char& unicode::operator[](size_t i) const {

}

size_t unicode::length() const {

}

}
