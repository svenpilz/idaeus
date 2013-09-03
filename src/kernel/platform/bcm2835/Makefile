BASE = ../../../..
NAME = kernel/platform/bcm2835
COMPILATION_UNITS = platform bootstrap framebuffer gpio mailbox uart
LIBS = c
include $(BASE)/configuration-executable.mk

LISTING = $(BUILDPATH)/bcm2835.listing

bcm2835: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS) $(STATIC_LIBS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build-executable.mk
