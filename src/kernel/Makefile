BASE = ../..
NAME = kernel
COMPILATION_UNITS = main syscall error_handler
LIBS = c graphics
DEPENDENCY = arch/arm platform/bcm2835
include $(BASE)/configuration-executable.mk

ELF = $(BUILDPATH)/kernel.elf
ELF_LISTING = $(BUILDPATH)/kernel.elf.listing
IMG_LISTING = $(BUILDPATH)/kernel.img.listing

kernel: $(DEPENDENCY_TARGETS) $(ELF_LISTING) $(IMG_LISTING)

$(ELF): $(OBJECTS) $(DEPENDENCY_OBJECTS) $(STATIC_LIBS)
	#TODO: bootstrap.o needs to be explicitly linked,
	#      otherwise it will not be included in the binary.
	#      How could this be done automatically?
	$(LINK) -o $@ -T kernel.ld $(BUILDPATH)/platform/bcm2835/bootstrap.o $^

$(ELF_LISTING): $(ELF)
	$(OBJDUMP) -d $^ > $@
	
$(BUILDPATH)/kernel.img: $(ELF)
	$(OBJCOPY) $^ -O binary $@
	
$(IMG_LISTING): $(BUILDPATH)/kernel.img
	$(OBJDUMP) -D -b binary -m $(TARGET_MACHINE) $^ > $@
	
qemu: kernel
	$(QEMU) $(QEMU_FLAGS) -kernel $(ELF) 
	
qemu-debug: kernel
	$(QEMU) $(QEMU_FLAGS) -s -S -kernel $(ELF) &
	$(GDB) --command=gdbinit-qemu $(ELF)
	
include $(BASE)/build-executable.mk
