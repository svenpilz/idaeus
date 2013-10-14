BASE = ../../..
NAME = c++
COMPILATION_UNITS = shared_ptr
include $(BASE)/configuration-library.mk

ifdef COMPILE_FOR_LOCAL_UNIT_TEST
CXXFLAGS += -I $(BASE)/include/libc++ -I $(BASE)/include/libc
endif

LISTING = $(BUILDPATH)/c++.listing

libidaeus-unicode: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
