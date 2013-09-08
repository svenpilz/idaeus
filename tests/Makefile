BASE = ..
NAME = testrunner
LIBS = bitmap
COMPILE_FOR_LOCAL_UNIT_TEST = 1
include $(BASE)/configuration-executable.mk

all-tests: $(BUILDPATH)/testrunner
	$(BUILDPATH)/testrunner

$(BUILDPATH)/testrunner: testrunner.cpp $(BUILDPATH) $(STATIC_LIBS)
	g++ `pkg-config --libs --cflags cppunit` -g -o $@ $< $(STATIC_LIBS)
	
include $(BASE)/build-executable.mk
