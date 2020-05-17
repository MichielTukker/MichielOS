/*
	mm.c

	This is the physical memory manager.
	it only allocates or free's a page, without 
	knowing why or for who it is. 
*/

#include <sys/mm.h>
#include <types.h>
#include <stdio.h>

/* 
	TODO:   some kind of locking? 
		low mem (<16 megs) pages?
*/

void *allocpage(){
	unsigned long* page;
	page=(unsigned long*) *nextpage;
	printf("page address is: %x",*page);
	nextpage--;
	return (void*)page;
}

void freepage(void *page){
	++nextpage;
	*nextpage= (unsigned long*)page;	
}

void map_page(void *physical, void* virtual, char mask){
	unsigned long addr;
	unsigned long* pagedir;
	unsigned long* pagetable;
	unsigned long offset_pagedir,offset_pagetab;	

	addr=(unsigned long)virtual;
	asm("mov %%cr3, %0\n":"=r"(pagedir):);
	
	printf("pagedir address %x \n", pagedir);
	
	addr = (addr >>12);
	offset_pagedir = (addr>>10);
	offset_pagetab = (addr & 0x3ff);
	printf("offset_pagedir=%d, offset_pagetable=%d \n",offset_pagedir,offset_pagetab);

	pagetable= (unsigned long *)pagedir[offset_pagedir];
	if(!pagetable){
		pagetable=allocpage();
		pagedir[offset_pagedir]= (unsigned long)pagetable | mask;
	}
	pagetable[offset_pagetab]=(unsigned long)physical | mask;
}
