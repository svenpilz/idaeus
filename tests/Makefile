BASE = ..
NAME = testrunner
LIBS = bitmap idaeus-base
COMPILE_FOR_LOCAL_UNIT_TEST = 1
ADDITIONAL_CLEAN_OBJECTS = $(BUILDBASE)/test-libc++
include $(BASE)/configuration-executable.mk

all-tests: $(BUILDPATH)/testrunner
	$(BUILDPATH)/testrunner
	
debug: $(BUILDPATH)/testrunner
	gdb $(BUILDPATH)/testrunner

$(BUILDPATH)/testrunner: testrunner.cpp $(BUILDPATH) $(STATIC_LIBS)
	$(LIB_BUILD_ENV_VARS) make -C "libc++"
	g++ `pkg-config --libs --cflags cppunit` --std=c++11 -o $@ $< $(STATIC_LIBS) $(BUILDBASE)/test-libc++/test-libc++.o
	
include $(BASE)/build-executable.mk
