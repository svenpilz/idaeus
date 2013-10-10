#include <cppunit/ui/text/TestRunner.h>

#include "LibBitmapTest.h"
#include "LibIdaeusBaseStringTest.h"

int main( int argc, char **argv) {
	CppUnit::TextUi::TestRunner runner;
	
	runner.addTest(LibBitmapTest::suite());
	runner.addTest(LibIdaeusBaseStringTest::suite());
	
	runner.run();
	return 0;
}
