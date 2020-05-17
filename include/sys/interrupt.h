
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <types.h>
/*
 * Interrupt types
 */
#define INT_0 0x8E00     // 1000111000000000 = present,ring0,int_gate
#define INT_3 0xEE00     // 1110111000000000 = present,ring3,int_gate


/* structure for an interrupt */
struct _interrupt
{
	word low_offset;                         // low nibble of offset to handler of interrupt 
	word selector;                           // GDT selector used 
	word settings;                           // settings for int 
	word high_offset;                        // high nibble to handler code 
}__attribute__ ((packed)) ;


/* structure for the IDTR */
struct _idtr
{
     word limit;                             // limit or Size of IDT 
     struct _interrupt *base;                    // a pointer to the base of the IDT 
}__attribute__ ((packed)) ;

typedef struct _interrupt interrupt;
typedef struct _idtr idtr;

#endif
