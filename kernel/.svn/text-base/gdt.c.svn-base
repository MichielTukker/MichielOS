/*
	gdt.c 
		the routines for manipulating the Global
		Descriptor table.
*/

#include <sys/gdt.h>

struct gdt_ptr gp;
struct gdt_entry gdt[3];

void gdt_fill_descriptor(int num, unsigned long base, unsigned long limit,
			 unsigned char access, unsigned char gran){
	
	gdt[num].base_low = (base & 0xffff);
	gdt[num].base_middle = (base >> 16) & 0xff;
	gdt[num].base_high = (base >> 24) & 0xff;

	gdt[num].limit_low = (limit & 0xffff);
	gdt[num].granularity = ((limit >> 16) & 0x0f);

	gdt[num].granularity |= (gran & 0xf0);
	gdt[num].access = access;
}

void gdt_install(){
	gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
	gp.base = (unsigned int) &gdt;

	gdt_fill_descriptor(0,0,0,0,0);
	gdt_fill_descriptor(1,0,0xffffffff, 0x9a, 0xcf);
	gdt_fill_descriptor(2,0,0xffffffff, 0x92, 0xcf);

	gdt_flush();
}
