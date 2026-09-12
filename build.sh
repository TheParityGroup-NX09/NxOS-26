#!/bin/bash
set -e

nasm -f elf32 boot/boot.asm -o boot.o

g++ -m32 -c kernel/kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
ld -m elf_i386 -T boot/linker.ld -o myos.bin boot.o kernel.o

# cleanin
mkdir -p .iso_tmp/boot/grub

mv myos.bin .iso_tmp/boot/myos.bin
cat << EOF > .iso_tmp/boot/grub/grub.cfg
menuentry "NxOS 2" {
    multiboot /boot/myos.bin
    boot
}
EOF

grub-mkrescue -o myos.iso .iso_tmp
rm -rf .iso_tmp boot.o kernel.o
qemu-system-i386 -cdrom myos.iso -m 512
