# makefile for Gabriel
 LD = /usr/cross/bin/i586-elf-ld
 OBJ = main.o init.o gdt.o idt.o interrupts.o pic.o io.o

gabriel.img:	floppy.img kernel.bin menu.cfg
		cp floppy.img $@
		chmod +w $@
		mcopy -o -i $@ $< ::/boot
		mcopy -o -i $@ menu.cfg ::/boot

kernel.bin:	link.ld loader.o $(OBJ) 
		$(LD) -o  $@ -nostdlib -T $^ 		

loader.o:	
	(cd ../boot && make)

$(OBJ):
	(cd ../kernel && make)
