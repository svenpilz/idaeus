ifdef COMPILE_FOR_LOCAL_UNIT_TEST
BUILDBASE = $(BASE)/build/tests
else
BUILDBASE = $(BASE)/build/idaeus
endif

BUILDPATH_LIB = $(BUILDBASE)/lib
SRCBASE = $(BASE)/src
SRC_LIB = $(SRCBASE)/lib

ARCH = arm
ABI = $(ARCH)-none-eabi
TARGET_MACHINE = armv5te
QEMU_FLAGS = -cpu arm1176 -m 256 -M raspi -serial stdio

BASE_COMPILER_FLAGS = -fno-builtin -I $(BASE)/include -c
BASE_COMPILER_FLAGS += -o2
BASE_COMPILER_FLAGS += -g

CXXFLAGS = $(BASE_COMPILER_FLAGS)
CXXFLAGS += --std=c++11

CFLAGS = $(BASE_COMPILER_FLAGS)
CFLAGS += --std=gnu11

ifdef COMPILE_FOR_LOCAL_UNIT_TEST
LINK = ld
OBJCOPY = objcopy
OBJDUMP = objdump
CC = gcc
CXX = g++
GDB = gdb
PACK = ar rs
else
TOOLCHAIN = $(BASE)/bin/toolchain/bin
LINK = $(TOOLCHAIN)/$(ABI)-ld
OBJCOPY = $(TOOLCHAIN)/$(ABI)-objcopy
OBJDUMP = $(TOOLCHAIN)/$(ABI)-objdump
CC = $(TOOLCHAIN)/$(ABI)-gcc
CXX = $(TOOLCHAIN)/$(ABI)-g++
GDB = $(TOOLCHAIN)/$(ABI)-gdb
PACK = $(TOOLCHAIN)/$(ABI)-ar rs
QEMU = $(TOOLCHAIN)/qemu-system-$(ARCH) #-d int
CFLAGS += -mcpu=arm1176jzf-s -I $(BASE)/include/libc
CXXFLAGS += -mcpu=arm1176jzf-s -I $(BASE)/include/libc
endif

