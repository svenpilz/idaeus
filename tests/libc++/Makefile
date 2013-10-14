BASE = ../..
NAME = test-libc++
COMPILATION_UNITS = shared_ptr
LIBS = c++
COMPILE_FOR_LOCAL_UNIT_TEST = 1
include $(BASE)/configuration-executable.mk

CXXFLAGS += -nostdinc++ -I $(BASE)/include/libc++

$(NAME): $(BUILDPATH) $(BUILDPATH)/$(NAME).o

$(BUILDPATH)/$(NAME).o: $(OBJECTS) $(DEPENDENCY_OBJECTS) $(STATIC_LIBS)
	$(LINK) -Ur -o $@ $^

include $(BASE)/build-executable.mk
