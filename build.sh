#!/bin/sh
export PATH=/usr/cross/bin/:$PATH

cd kernel 
echo "compiling kernel sources"
i586-elf-gcc -I../include -c -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -Wall *.c
nasm -f elf -o interrupts.o interrupts.asm
mv *.o ../

cd ../mm
echo "compiling memory managment"
i586-elf-gcc -I../include -c -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -Wall *.c
mv *.o ../

cd ../lib
echo "compiling library functions"
i586-elf-gcc -I../include -c -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -Wall *.c
mv *.o ../

cd ../boot
echo "assembling kernel loader"
nasm -f elf -o loader.o loader.asm
mv loader.o ../

cd ../
echo "Linking..."
i586-elf-ld -T build/link.ld -nostdlib -o kernel.bin  \
	loader.o main.o init.o gdt.o idt.o pic.o interrupts.o io.o phys.o stdio.o string.o
echo -n "cleaning up..."
rm *.o


echo "building image:"
cp build/floppy.img gabriel.img
chmod +w gabriel.img
mcopy -o -i gabriel.img kernel.bin ::/boot
mcopy -o -i gabriel.img build/menu.cfg ::/boot
#rm kernel.bin
echo "done."
