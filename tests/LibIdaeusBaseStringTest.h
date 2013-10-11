#ifndef TESTS_LIBIDAEUSUNICODE
#define TESTS_LIBIDAEUSUNICODE

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

#include "../include/idaeus/base/string.h"

using namespace idaeus;

class LibIdaeusBaseStringTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(LibIdaeusBaseStringTest);
CPPUNIT_TEST(testFromUTF8);
CPPUNIT_TEST_SUITE_END();

private:
	
	
public:
	void setUp() {
		
	}

	void tearDown() {
		
	}

	void testFromUTF8() {
		unicode_char ucs[] = {0x48, 0xe4, 0x6c, 0x6c, 0x6f, 0x20, 0x201e, 0x53, 0x74, 0x72, 0x65, 0xdf, 0x74, 0x65, 0x73, 0x74, 0x201c, 0x21};
		String u = String::fromUTF8("Hällo „Streßtest“!");
		CPPUNIT_ASSERT_EQUAL_MESSAGE("length as unicode_char", (size_t)18, u.length());
		
		for (size_t i = 0; i < u.length(); ++i) {
			CPPUNIT_ASSERT_EQUAL_MESSAGE("ucs compare", ucs[i], u[i]);
		}puts("bl");
	}
};

#endif
