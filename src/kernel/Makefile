TOOLCHAIN = ../../bin/toolchain/bin
COMPILER_PREFIX = $(TOOLCHAIN)/arm-none-eabi
CC = $(COMPILER_PREFIX)-gcc --std=gnu11 -fno-builtin  -o2 -mcpu=arm1176jzf-s -I ../../include/libc -g -c
LINK = $(COMPILER_PREFIX)-ld
BUILD_PREFIX = ../../build/idaeus
BUILD = $(BUILD_PREFIX)/kernel

all: kernel
kernel: $(BUILD)/kernel.img $(BUILD)/kernel.img.asm $(BUILD)/kernel.listing

$(BUILD)/kernel.img: $(BUILD)/kernel.elf
	$(COMPILER_PREFIX)-objcopy $< -O binary $@
	
$(BUILD)/kernel.img.asm: $(BUILD)/kernel.img
	$(COMPILER_PREFIX)-objdump -D -b binary -m armv5te $< > $@
	
$(BUILD)/kernel.listing: $(BUILD)/kernel.elf
	$(COMPILER_PREFIX)-objdump -d $< > $(BUILD)/kernel.listing

$(BUILD)/kernel.elf: $(BUILD) Makefile kernel.ld $(BUILD)/bootstrap.o $(BUILD)/main.o
	$(LINK) -o $(BUILD)/kernel.elf -T kernel.ld $(BUILD)/bootstrap.o $(BUILD)/main.o $(BUILD)/driver/bcm2835.o $(BUILD_PREFIX)/lib/c.o
	
$(BUILD)/%.o: %.s
	$(CC) -o $@ $<
	
$(BUILD)/%.o: %.c
	$(CC) -o $@ $<
	
$(BUILD):
	mkdir -p $@
	
$(BUILD)/driver/bcm2835/gpio:
	mkdir -p $@
	
$(BUILD)/driver/bcm2835/uart:
	mkdir -p $@
	
qemu: kernel
	$(TOOLCHAIN)/qemu-system-arm -kernel $(BUILD)/kernel.elf -cpu arm1176 -m 256 -M raspi -serial stdio
	
qemu-debug: kernel
	$(TOOLCHAIN)/qemu-system-arm -s -S -kernel $(BUILD)/kernel.elf -cpu arm1176 -m 256 -M raspi -serial stdio &
	$(COMPILER_PREFIX)-gdb --command=gdbinit-qemu $(BUILD)/kernel.elf
	
clean:
	rm -rf $(BUILD)
