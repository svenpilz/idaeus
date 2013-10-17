#ifndef TESTS_LIBCXX_VECTOR_H
#define TESTS_LIBCXX_VECTOR_H

#include <cppunit/extensions/HelperMacros.h>

namespace vector_test {
	bool testPushBack();
}

class LibCxxVectorTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(LibCxxVectorTest);
CPPUNIT_TEST(testPushBack);
CPPUNIT_TEST_SUITE_END();
	
public:
	void setUp() {}
	void tearDown() {}
	
	void testPushBack() {
		CPPUNIT_ASSERT_EQUAL(true, vector_test::testPushBack());
	}
};

#endif
