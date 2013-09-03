BASE = ../../../..
NAME = kernel/arch/arm
COMPILATION_UNITS = arch interrupts vfp
include $(BASE)/configuration-executable.mk

arm: $(BUILDPATH) $(BUILDPATH).o

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^

include $(BASE)/build-executable.mk
