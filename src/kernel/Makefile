TOOLCHAIN = ../../bin/toolchain/bin
COMPILER_PREFIX = $(TOOLCHAIN)/arm-none-eabi
CC = $(COMPILER_PREFIX)-gcc -mcpu=arm1176jzf-s -I ../../include/libc -g -c
LINK = $(COMPILER_PREFIX)-ld
BUILD_PREFIX = ../../build/idaeus
BUILD = $(BUILD_PREFIX)/kernel

all: $(BUILD)/kernel.img $(BUILD)/kernel.img.asm $(BUILD)/kernel.listing

$(BUILD)/kernel.img: $(BUILD)/kernel.elf
	$(COMPILER_PREFIX)-objcopy $< -O binary $@
	
$(BUILD)/kernel.img.asm: $(BUILD)/kernel.img
	$(COMPILER_PREFIX)-objdump -D -b binary -m armv5te $< > $@
	
$(BUILD)/kernel.listing: $(BUILD)/kernel.elf
	$(COMPILER_PREFIX)-objdump -d $< > $(BUILD)/kernel.listing

$(BUILD)/kernel.elf: $(BUILD) kernel.ld $(BUILD)/bootstrap.o $(BUILD)/main.o
	$(LINK) -o $(BUILD)/kernel.elf -T kernel.ld $(BUILD)/bootstrap.o $(BUILD)/main.o
	
$(BUILD)/%.o: %.s
	$(CC) -o $@ $<
	
$(BUILD)/%.o: %.c
	$(CC) -o $@ $<
	
$(BUILD):
	mkdir -p $@
	
qemu: $(BUILD)/kernel.elf
	$(TOOLCHAIN)/qemu-system-arm -kernel $< -cpu arm1176 -m 256 -M raspi -serial stdio
	
qemu-debug: $(BUILD)/kernel.elf
	$(TOOLCHAIN)/qemu-system-arm -s -S -kernel $< -cpu arm1176 -m 256 -M raspi -serial stdio &
	$(COMPILER_PREFIX)-gdb --command=gdbinit-qemu $(BUILD)/kernel.elf
	
clean:
	rm -rf $(BUILD)
