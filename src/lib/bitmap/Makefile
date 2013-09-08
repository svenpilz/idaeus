BASE = ../../..
NAME = bitmap
COMPILATION_UNITS = bitmap
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/bitmap.listing

libbitmap: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
