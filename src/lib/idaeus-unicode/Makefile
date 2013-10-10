BASE = ../../..
NAME = idaeus-unicode
COMPILATION_UNITS = unicode
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/idaeus-unicode.listing

libidaeus-unicode: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
