#!/usr/bin/sh

# -fsanitize=undefined,unsigned-integer-overflow,local-bounds

clang -Oz -g --target=i586-unknown-elf -march=i586 -ffreestanding -fno-builtin -nostdlib -nostdlibinc \
      -I ../../libnop/include $(find . -name "*.c") -c -D_DEFAULT_SOURCE -DUSEASM
find . -name "*.asm" -exec nasm -O4 -felf {} \;

i586-elf-ld -T link_bin.ld -nostdlib $(find . -name "*.o") $(find ../../libnop -name "*.o") -o doom.nex
i586-elf-ld -T link_elf.ld -nostdlib $(find . -name "*.o") $(find ../../libnop -name "*.o") -o doom.elf
