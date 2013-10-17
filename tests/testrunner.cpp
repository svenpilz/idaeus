#include <cppunit/ui/text/TestRunner.h>

#include "LibBitmapTest.h"
#include "LibIdaeusBaseStringTest.h"
#include "libc++/libc++.h"

int main( int argc, char **argv) {
	CppUnit::TextUi::TestRunner runner;
	
	runner.addTest(LibBitmapTest::suite());
	runner.addTest(LibIdaeusBaseStringTest::suite());
	runner.addTest(LibCxxSharedPtrTest::suite());
	runner.addTest(LibCxxSharedPtrTest::suite());
	runner.addTest(LibCxxVectorTest::suite());
	
	runner.run();
	return 0;
}
