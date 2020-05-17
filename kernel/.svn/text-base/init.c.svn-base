/* init.c
	Initialisation for the memory and page manager.
*/

#include <stdio.h>
#include <sys/mm.h>

void init_paging(){

	void *kernelpagedirPTR = 0;
	void *kernelpagetablePTR =0;
	int i=0;
	
	/* 	the + 0x40000000 corrects the address (paging hasn't 
		been enabled yet)
	*/		
	kernelpagedirPTR = (char *)kernelpagedir + 0x40000000;
	kernelpagetablePTR = (char *)pagetable + 0x40000000;

/*
	We'll fill the page dir with zero's, and map the first
	4mb into the pagetable. we also set the present and r/w
	flags of the page table entry. we leave the 3rd bit cleared,
	so that it has ring0 access rights.
*/
	for(i=0;i<1024;i++){
		pagetable[i] = (i * 4096) | 0x3;
		kernelpagedir[i] = 0;		
	}
	
	kernelpagedir[0] = (unsigned long) kernelpagetablePTR | 0x3;
	kernelpagedir[768] = (unsigned long) kernelpagetablePTR | 0x3;

	asm volatile (	"mov %0, %%eax\n"
					"mov %%eax, %%cr3\n"
					"mov %%cr0, %%eax\n"
					"orl $0x80000000, %%eax\n"
					"mov %%eax, %%cr0\n" :: "m" (kernelpagedirPTR));
}


void init_page_manager(unsigned long memory){
	unsigned long *stack;
	unsigned long num_pages=(memory)/4;
	unsigned long i;

	stack = &_kernelend;
	printf("end of kernel: %x\n",stack);
	
	for(i=0;i<=(num_pages-1);i++){
		stack[i]=4096*i;
	}
	stack[i]=4096*i;	/* for the last page */
	nextpage=&stack[i];
}

