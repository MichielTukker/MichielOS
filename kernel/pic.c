/*
	pic.cpp
*/

#include <sys/pic.h>
#include <sys/io.h>

void disable_ints() //disables interrupts
{
  __asm__ __volatile__("cli" : :);
}

void enable_ints() //enables interrupts
{
  __asm__ __volatile__("sti" : :);
}

void init_pic()
{

	outb(0x20, 0x11);	//signal the first PIC
	outb(0xa0, 0x11);   //signal second PIC
	
	outb(0x21, 0x20);	//first PIC has int 0x20-0x27
	outb(0xa1, 0x28);	//second PIC has int 0x28-0x2f

	outb(0x21, 0x04);	//this tells the PIC's how they're cascaded.
	outb(0xA1, 0x02);	// pic1 uses irq2, and pic2 uses irq9

	outb(0x21, 0x01);	// last init byte for both pic's
	outb(0xA1, 0x01);
	
	outb(0x21, 0xff);
	outb(0xA1, 0xff);
		
}
