BASE = ../../..
NAME = c
COMPILATION_UNITS = delay string math putc puts printf gcc_arm_arith gcc_arm_arith_abi
include $(BASE)/configuration-library.mk

LISTING = $(BUILDPATH)/c.listing

libc: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
