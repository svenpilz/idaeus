TOOLCHAIN = ../../../bin/toolchain/bin
COMPILER_PREFIX = $(TOOLCHAIN)/arm-none-eabi
CC = $(COMPILER_PREFIX)-gcc --std=gnu11 -fno-builtin  -o2 -mcpu=arm1176jzf-s -I ../../../include/libc -I ../../../include -g -c
PACK = $(COMPILER_PREFIX)-ar rs
BUILD_PREFIX = ../../../build/idaeus/lib
BUILD = $(BUILD_PREFIX)/graphics

all: $(BUILD) libgraphics $(BUILD_PREFIX)/libgraphics.listing
libgraphics: $(BUILD)/compositor.o $(BUILD)/primitives.o $(BUILD)/color.o
	$(PACK) $(BUILD_PREFIX)/graphics.o $^
	
$(BUILD_PREFIX)/libgraphics.listing: $(BUILD_PREFIX)/graphics.o
	$(COMPILER_PREFIX)-objdump -d $< > $@
	
$(BUILD)/%.o: %.c
	$(CC) -o $@ $<
	
$(BUILD)/%.o: %.s
	$(CC) -o $@ $<
	
$(BUILD):
	mkdir -p $@
	
clean:
	rm -rf $(BUILD)
