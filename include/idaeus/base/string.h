#ifndef INCLUDE_IDAEUS_BASE_STRING_H
#define INCLUDE_IDAEUS_BASE_STRING_H

#include <cstddef>

namespace idaeus {
	typedef unsigned int unicode_char;
	
	class String {
	public:
		static String fromUTF8(const char* str);
		
		String(size_t len);
		~String();
		
		unicode_char& operator[](size_t i);
		size_t length() const;
		void append(unicode_char c);
		
	private:
		unicode_char* data;
		size_t datalen;
		size_t stringlen;
		
		void adjustSize(size_t len);
	};
}

#endif
