BASE = ../../..
NAME = c++
COMPILATION_UNITS = shared_ptr
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/c++.listing

libidaeus-unicode: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
