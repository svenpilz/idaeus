BUILDBASE = $(BASE)/build/idaeus
BUILDPATH_LIB = $(BUILDBASE)/lib
SRCBASE = $(BASE)/src
SRC_LIB = $(SRCBASE)/lib

ARCH = arm
ABI = $(ARCH)-none-eabi
TARGET_MACHINE = armv5te
QEMU_FLAGS = -cpu arm1176 -m 256 -M raspi -serial stdio

TOOLCHAIN = $(BASE)/bin/toolchain/bin
LINK = $(TOOLCHAIN)/$(ABI)-ld
OBJCOPY = $(TOOLCHAIN)/$(ABI)-objcopy
OBJDUMP = $(TOOLCHAIN)/$(ABI)-objdump
CC = $(TOOLCHAIN)/$(ABI)-gcc
GDB = $(TOOLCHAIN)/$(ABI)-gdb
PACK = $(TOOLCHAIN)/$(ABI)-ar rs
QEMU = $(TOOLCHAIN)/qemu-system-$(ARCH) -d int

CFLAGS = --std=gnu11 -fno-builtin -I $(BASE)/include/libc -I $(BASE)/include -c
CFLAGS += -mcpu=arm1176jzf-s
CFLAGS += -o2
CFLAGS += -g
