TOOLCHAIN = ../../../../bin/toolchain/bin
COMPILER_PREFIX = $(TOOLCHAIN)/arm-none-eabi
CC = $(COMPILER_PREFIX)-gcc --std=gnu11 -fno-builtin  -o2 -mcpu=arm1176jzf-s -I ../../../../include/libc -I ../../../../include -g -c
PACK = $(COMPILER_PREFIX)-ar rs
BUILD_PREFIX = ../../../../build/idaeus/kernel/driver
BUILD = $(BUILD_PREFIX)/bcm2835
VPATH = framebuffer gpio mailbox uart

$(BUILD_PREFIX)/bcm2835.o: $(BUILD)/framebuffer/framebuffer.o $(BUILD)/gpio/gpio.o $(BUILD)/mailbox/mailbox.o $(BUILD)/uart/uart.o
	$(PACK) $(BUILD_PREFIX)/bcm2835.o $^
	
$(BUILD)/%.o: %.c $(dir $@)
	mkdir -p $(dir $@)
	$(CC) -o $@ $<
	
clean:
	rm -rf $(BUILD)
	rm -f $(BUILD_PREFIX)/bcm2835.o
