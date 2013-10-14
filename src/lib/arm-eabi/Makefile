BASE = ../../..
NAME = arm-eabi
COMPILATION_UNITS = udiv udivmod
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/arm-eabi.listing

libc: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
