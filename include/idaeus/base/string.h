#ifndef INCLUDE_IDAEUS_BASE_STRING_H
#define INCLUDE_IDAEUS_BASE_STRING_H

#include <cstddef>
#include <memory>
#include <vector>

namespace idaeus {
	typedef unsigned int unicode_char;
	
	class String {
	public:
		static String fromUTF8(const char* str);
		
		String();
		String(size_t n);
		
		unicode_char& operator[](size_t i);
		size_t length() const;
		void append(unicode_char c);
		
	private:
		std::shared_ptr< std::vector<unicode_char> > _data;
	};
}

#endif
