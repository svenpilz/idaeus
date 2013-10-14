#ifndef TESTS_LIBCXX_SHARED_PTR_H
#define TESTS_LIBCXX_SHARED_PTR_H

#include <cppunit/extensions/HelperMacros.h>

namespace shared_ptr_test {
	bool testCopyConstructor();
}

class LibCxxSharedPtrTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(LibCxxSharedPtrTest);
CPPUNIT_TEST(testCopyConstructor);
CPPUNIT_TEST_SUITE_END();
	
public:
	void setUp() {}
	void tearDown() {}
	
	void testCopyConstructor() {
		CPPUNIT_ASSERT_EQUAL(true, shared_ptr_test::testCopyConstructor());
	}
};

#endif
