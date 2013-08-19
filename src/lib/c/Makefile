TOOLCHAIN = ../../../bin/toolchain/bin
COMPILER_PREFIX = $(TOOLCHAIN)/arm-none-eabi
CC = $(COMPILER_PREFIX)-gcc -fno-builtin --std=gnu11 -I ../../../include/libc -g -c
PACK = $(COMPILER_PREFIX)-ar rs
BUILD_PREFIX = ../../../build/idaeus/lib
BUILD = $(BUILD_PREFIX)/c

all: $(BUILD) libc
libc: $(BUILD)/delay.o $(BUILD)/putc.o $(BUILD)/puts.o
	$(PACK) $(BUILD_PREFIX)/c.o $^
	
$(BUILD)/%.o: %.c
	$(CC) -o $@ $<
	
$(BUILD):
	mkdir -p $@
