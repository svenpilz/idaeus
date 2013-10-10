#include <cstdint>

namespace idaeus {
	typedef unsigned int unicode_char;
	
	class unicode {
	public:
		static unicode fromUTF8(const char* str);
		
		unicode(size_t len);
		~unicode();
		
		unicode_char& operator[](size_t i) const;
		size_t length() const;
	};
}
