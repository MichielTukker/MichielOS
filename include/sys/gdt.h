/* gdt.h
	basic structures and declarations for gdt.c functions
*/

struct gdt_ptr{
	unsigned short limit;
	unsigned int base;
} __attribute__ ((packed));


struct gdt_entry{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__ ((packed));


/* our assembler function  */
void gdt_flush();

void gdt_fill_descriptor(int num, unsigned long base, unsigned long limit,
						 unsigned char access, unsigned char gran);
void gdt_install();
