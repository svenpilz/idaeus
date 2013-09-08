#ifndef TESTS_LIBBITMAP
#define TESTS_LIBBITMAP

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "../include/bitmap.h"
}

static const bit_position_t bits_per_bucket = sizeof(bitmap_bucket_t) * 8;


class LibBitmapTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(LibBitmapTest);
CPPUNIT_TEST(testBitmapBucketCount);
CPPUNIT_TEST(testBitmapUnsetAll);
CPPUNIT_TEST(testBitmapSetAll);
CPPUNIT_TEST(testBitmapIsSet);
CPPUNIT_TEST(testBitmapUnset);
CPPUNIT_TEST(testBitmapSet);
CPPUNIT_TEST(testBitmapUnsetRange);
CPPUNIT_TEST(testBitmapSetRange);
CPPUNIT_TEST(testBitmapCountUnset);
CPPUNIT_TEST(testBitmapCountSet);
CPPUNIT_TEST_SUITE_END();

private:
	bitmap_t* bitmap;
	
public:
	void setUp() {
		bitmap = new bitmap_t;
		size_t bc = bitmap_bucket_count(1024);
		bitmap->buckets = new bitmap_bucket_t[bc];
		bitmap->number_of_buckets = bc;
	}

	void tearDown() {
		delete[] bitmap->buckets;
		delete bitmap;
	}

	void testBitmapBucketCount() {
		CPPUNIT_ASSERT_EQUAL((size_t)1, bitmap_bucket_count(3));
		CPPUNIT_ASSERT_EQUAL((size_t)1, bitmap_bucket_count(bits_per_bucket));
		CPPUNIT_ASSERT_EQUAL((size_t)2, bitmap_bucket_count(bits_per_bucket+1));
	}
	
	void testBitmapUnsetAll() {
		bit_position_t b;
		bitmap_unset_all(bitmap);	
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_first_set", -1, bitmap_first_set(bitmap, &b));
	}
	
	void testBitmapSetAll() {
		bit_position_t b;
		bitmap_set_all(bitmap);	
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_first_set", 0, bitmap_first_set(bitmap, &b));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("position", (bit_position_t)0, b);
	}
	
	void testBitmapIsSet() {
		bitmap_unset_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_set", 0, bitmap_set(bitmap, 2));		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on unset bit", 0, bitmap_is_set(bitmap, 1));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, 2));
	}
	
	void testBitmapUnset() {
		bitmap_set_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 1, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 1, bitmap_is_set(bitmap, bits_per_bucket+1));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", 0, bitmap_unset(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", 0, bitmap_unset(bitmap, bits_per_bucket+1));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", -1, bitmap_unset(bitmap, 1024));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 0, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 0, bitmap_is_set(bitmap, bits_per_bucket+1));
	}
	
	void testBitmapSet() {
		bitmap_unset_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 0, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 0, bitmap_is_set(bitmap, bits_per_bucket+1));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", 0, bitmap_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", 0, bitmap_set(bitmap, bits_per_bucket+1));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", -1, bitmap_set(bitmap, 1024));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, bits_per_bucket+1));
	}
	
	void testBitmapUnsetRange() {
		bitmap_set_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 1, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 1, bitmap_is_set(bitmap, bits_per_bucket+1));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset_range", 0, bitmap_unset_range(bitmap, 0, bits_per_bucket+2));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset_range", -1, bitmap_unset_range(bitmap, 0, 1025));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on unset bit", 0, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on unset bit", 0, bitmap_is_set(bitmap, bits_per_bucket));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on unset bit", 0, bitmap_is_set(bitmap, bits_per_bucket+1));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, bits_per_bucket+2));
	}
	
	void testBitmapSetRange() {
		bitmap_unset_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 0, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set", 0, bitmap_is_set(bitmap, bits_per_bucket+1));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_set_range", 0, bitmap_set_range(bitmap, 0, bits_per_bucket+2));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_set_range", -1, bitmap_set_range(bitmap, 0, 1025));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, 0));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, bits_per_bucket));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on set bit", 1, bitmap_is_set(bitmap, bits_per_bucket+1));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_is_set on unset bit", 0, bitmap_is_set(bitmap, bits_per_bucket+2));
	}
	
	void testBitmapCountUnset() {
		bitmap_unset_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_count_unset", (bit_position_t)1024, bitmap_count_unset(bitmap));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_set_range", 0, bitmap_set_range(bitmap, 0, bits_per_bucket));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_set", 0, bitmap_set(bitmap, bits_per_bucket+1));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_count_unset", (bit_position_t)1024 - bits_per_bucket - 1, bitmap_count_unset(bitmap));
	}
	
	void testBitmapCountSet() {
		bitmap_set_all(bitmap);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_count_set", (bit_position_t)1024, bitmap_count_set(bitmap));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset_range", 0, bitmap_unset_range(bitmap, 0, bits_per_bucket));
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_unset", 0, bitmap_unset(bitmap, bits_per_bucket+1));
		
		CPPUNIT_ASSERT_EQUAL_MESSAGE("bitmap_count_unset", (bit_position_t)1024 - bits_per_bucket - 1, bitmap_count_set(bitmap));
	}
};

#endif
