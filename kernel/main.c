/* Main kernel file. */

#include <sys/init.h>
#include <sys/mm.h>
#include <sys/io.h>
#include <sys/gdt.h>
#include <sys/pic.h>
#include <sys/idt.h>
#include <sys/interrupt.h>
#include <sys/isr.h>
#include <sys/multiboot.h>

#include <string.h>
#include <stdio.h>
#include <types.h>

void panic(char msg[]){
        int i=0;
	unsigned short *vid = ((unsigned short *)0xc00b8000);
	unsigned char attr = 0x07;
        for (i=0;msg[i]!='\0';i++)
                vid[i]=(attr<<8)|msg[i];
}

void _int_handler(int int_number){
	disable_ints();
	switch(int_number)
	{
	default:
		{
			asm volatile(	"mov $0xdeadbeef, %%eax \n"
					"hlt"::);
			break;
		}
	}	
	enable_ints();
}

void _main( unsigned long addr, unsigned int magic ){
	unsigned long mem=0;
	multiboot_info_t* mbd = (multiboot_info_t*)addr;

	void* testpage=0;
	int* test=0;
	char *memory;
	int a;

	init_paging();
	gdt_install();
	clear();

	if(magic!=0x2BADB002)
		panic("No multiboot loader");
	if( mbd->flags&0x01 ){
		mem= mbd->mem_upper-3072;   
		init_page_manager(mem);/* we've already used and mapped the first 4 megs */
	} else {
		panic("multiboot flag isn't set.");
	}	
	
	
	disable_ints();
	init_pic();
	loadexceptions();
	loadidt();
	enable_ints(); 
	printf("memory = %d \n", mem);
	
	testpage=allocpage();
	printf("addres of page: %x\n",*((int*)testpage));
	map_page(testpage, (void*)0x60002000, 0x3);
	test= (int*)0x6002000;
	*test=5;
	
/*	memory = itoa((int)mem,10);
	panic(itoa((int)(mem+4096),10));
*/
	while(1){}
}

