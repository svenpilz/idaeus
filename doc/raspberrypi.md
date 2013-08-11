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
