BASE = ../../../..
NAME = kernel/arch/arm
COMPILATION_UNITS = arch interrupts interrupt_handler vfp
include $(BASE)/configuration-executable.mk

LISTING = $(BUILDPATH)/arm.listing

arm: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build-executable.mk
