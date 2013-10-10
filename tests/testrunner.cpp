#include <cppunit/ui/text/TestRunner.h>

#include "LibBitmapTest.h"
#include "LibIdaeusUnicodeTest.h"

int main( int argc, char **argv) {
	CppUnit::TextUi::TestRunner runner;
	
	runner.addTest(LibBitmapTest::suite());
	runner.addTest(LibIdaeusUnicodeTest::suite());
	
	runner.run();
	return 0;
}
