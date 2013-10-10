BASE = ../../..
NAME = idaeus-base
COMPILATION_UNITS = string
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/idaeus-base.listing

libidaeus-unicode: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
