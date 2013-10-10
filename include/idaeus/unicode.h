#ifndef INCLUDE_IDAEUS_UNICODE_H
#define INCLUDE_IDAEUS_UNICODE_H

#include <cstddef>

namespace idaeus {
	typedef unsigned int unicode_char;
	
	class unicode {
	public:
		static unicode fromUTF8(const char* str);
		
		unicode(size_t len);
		~unicode();
		
		unicode_char& operator[](size_t i);
		size_t length() const;
		void append(unicode_char c);
		
	private:
		unicode_char* string;
		size_t stringlen;
		size_t contentlen;
		
		void adjustSize(size_t len);
	};
}

#endif
