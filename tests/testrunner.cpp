#include <cppunit/ui/text/TestRunner.h>

#include "LibBitmapTest.h"

int main( int argc, char **argv) {
	CppUnit::TextUi::TestRunner runner;
	
	runner.addTest(LibBitmapTest::suite());
	
	runner.run();
	return 0;
}
