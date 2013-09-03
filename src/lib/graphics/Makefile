BASE = ../../..
NAME = graphics
COMPILATION_UNITS = compositor primitives color
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/c.listing

libc: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
