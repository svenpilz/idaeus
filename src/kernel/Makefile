TOOLCHAIN = ../../bin/toolchain/bin
COMPILER_PREFIX = $(TOOLCHAIN)/arm-none-eabi
CC = $(COMPILER_PREFIX)-gcc -c
LINK = $(COMPILER_PREFIX)-ld
BUILD_PREFIX = ../../build/idaeus
BUILD = $(BUILD_PREFIX)/kernel

$(BUILD)/kernel.elf: $(BUILD) $(BUILD)/bootstrap.o $(BUILD)/main.o
	$(LINK) -o $(BUILD)/kernel.elf $(BUILD)/bootstrap.o $(BUILD)/main.o

$(BUILD)/%.o: %.s
	$(CC) -o $@ $<
	
$(BUILD)/%.o: %.c
	$(CC) -o $@ $<
	
$(BUILD):
	mkdir -p $@
	
make qemu: $(BUILD)/kernel.elf
	$(TOOLCHAIN)/qemu-system-arm -kernel $< -cpu arm1176 -m 256 -M raspi -serial stdio
	
clean:
	rm -rf $(BUILD)
