#ifndef TESTS_LIBIDAEUSUNICODE
#define TESTS_LIBIDAEUSUNICODE

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "../include/idaeus/unicode.h"
}


class LibIdaeusUnicodeTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(LibIdaeusUnicodeTest);
//CPPUNIT_TEST(testBitmapBucketCount);
CPPUNIT_TEST_SUITE_END();

private:
	
	
public:
	void setUp() {
		
	}

	void tearDown() {
		
	}

	
};

#endif
