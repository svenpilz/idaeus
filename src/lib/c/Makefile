BASE = ../../..
NAME = c
COMPILATION_UNITS = delay string math putc puts printf
include $(BASE)/configuration-library.mk

ifdef COMPILE_FOR_LOCAL_UNIT_TEST
CFLAGS += -I $(BASE)/include/libc
endif

LISTING = $(BUILDPATH)/c.listing

libc: $(BUILDPATH) $(LISTING)

$(BUILDPATH).o: $(OBJECTS)
	$(PACK) $@ $^
	
$(LISTING): $(BUILDPATH).o
	$(OBJDUMP) -d $^ > $@

include $(BASE)/build.mk
