#!/bin/bash
set -e

rm -rf build .iso_tmp myos.iso
mkdir -p build

INCLUDE_FLAGS=""
for dir in $(find . -type d); do
    if ls "$dir"/*.h* &>/dev/null; then
        INCLUDE_FLAGS="$INCLUDE_FLAGS -I$dir"
    fi
done

OBJECTS=""

for asm_file in $(find . -type f -name "*.asm"); do
    obj_file="build/$(basename "${asm_file%.*}").o"
    nasm -f elf32 "$asm_file" -o "$obj_file"
    OBJECTS="$OBJECTS $obj_file"
done

for cpp_file in $(find . -type f -name "*.cpp"); do
    obj_file="build/$(basename "${cpp_file%.*}").o"
    g++ -m32 -c "$cpp_file" -o "$obj_file" $INCLUDE_FLAGS -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
    OBJECTS="$OBJECTS $obj_file"
done

LINKER_SCRIPT=$(find . -type f -name "*.ld" | head -n 1)
if [ -z "$LINKER_SCRIPT" ]; then
    echo "Error: No linker script (.ld) found!"
    exit 1
fi

mkdir -p .iso_tmp/boot/grub
ld -m elf_i386 -T "$LINKER_SCRIPT" -o .iso_tmp/boot/myos.bin $OBJECTS

cat << EOF > .iso_tmp/boot/grub/grub.cfg
menuentry "NxOS-26" {
    multiboot /boot/myos.bin
    boot
}
EOF

grub-mkrescue -o myos.iso .iso_tmp
rm -rf .iso_tmp

qemu-system-i386 -cdrom myos.iso
