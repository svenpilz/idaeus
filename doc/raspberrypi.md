# Raspberry Pi
## Hardware
* https://github.com/raspberrypi/linux/wiki/How-to-boot-using-device-tree

## Virtualization
### qemu
    apt-get build-dep qemu
    git clone https://github.com/Torlus/qemu.git qemu-rpi
    cd qemu-rpi
    mkdir build
    cd build
    ../configure --target-list=arm-softmmu --enable-sdl
    make

## Compiler
### gcc (Version 4.8)
Install build-dependencies for *binutils* and *gcc*:
    # apt-get build-dep binutils
    # apt-get build-dep gcc-4.8

Download the sources:
    $ wget ftp://sourceware.org/pub/binutils/snapshots/binutils-2.23.52.tar.bz2
    $ wget http://ftp.gnu.org/gnu/gcc/gcc-4.8.1/gcc-4.8.1.tar.bz2
    $ tar xjf binutils-2.23.52.tar.bz2
    $ tar xjf gcc-4.8.1.tar.bz2
    $ mkdir binutils-2.23.52/build
    $ mkdir gcc-4.8.1/build

Build the toolchain:
    $ export PREFIX=$HOME/bin/compiler
    $ cd binutils-2.23.52/build
    $ ../configure --prefix=$PREFIX --target=arm-none-eabi
    $ make
    $ make install
    $ cd ../../gcc-4.8.1/build
    $ PATH=$PATH:$PREFIX/bin ../configure --prefix=$PREFIX --target=arm-none-eabi --enable-interwork --enable-languages=c,c++ --without-headers
    $ make all-gcc
    $ make install-gcc

