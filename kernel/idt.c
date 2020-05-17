/*
	idt.c
*/

#include <sys/idt.h>
#include <types.h>
#include <sys/interrupt.h>
#include <sys/isr.h>



interrupt IDT[256];   /*de IDT table. de x86 heeft een max van 256 interrupts. */


void addint(int number, void (*handler)(), dword dpl){

/*		int number		het nummer van de interrupt die we gebruiken

		void (*handler)() 	een pointer naar de ISR-functie. deze zijn 
					geimplementeerd in assembler. deze assembler functies
					staan in isr.asm

		dword dpl		dpl is het privilege level. dit kan Ring0 of Ring3 zijn.
					het ring0...ring3 principe. dit zijn privilege levels. 
					we gebruiken alleen ring0 en ring3.  ring1 en ring2 bestaan 
					ook. Intel heeft deze 2 levels er ook bij gegooid, maar 
					voor zover ik weet, gebruikt niemand ze. 
					deze privilege levels bepalen of code toegang heeft tot de 
	2				IDT.  basically,   de Kernel (Ring0) heeft wel toegang,  en 
					de userland (Ring3) niet. 

		
	met deze functie kunnen we interrupts koppelen aan ISR's (interupt service routines)
	deze functie gebruikt een structure genaamd idt_entry. (zie descriptor.h voor de 
	structure)  hier vullen we de nodige velden in. 
*/
	word selector = 0x08;  /* een tijdelijke waarde voor de selector*/
	word settings;
	dword offset = (dword)handler; 
	
/*	de selector variabele is ons code segment. deze halen we uit het cs register
	met een simpele assembler instructie
*/	
	asm volatile("mov %%cs, %0" : "=g"(selector));
	

/*	de settings zijn niet echt van belang om hier uit te gaan leggen. elke 
	tutorial geeft er een goede uitleg over.  de enige belangrijke setting is 
	die van de privilege levels. vandaar de variable-names
*/
	switch(dpl){
		case 0:  settings = INT_0; break;
		case 1:
		case 2:
		case 3:  settings = INT_3; break;
	}

/*	Low_offset en High_offset. 
	de offset (het adres naar onze Interupt Service Routine) is verdeeld in
	2 stukken, namelijk Low_offset en High_offset. dit is gedaan om compatible 
	te zijn met de 286.  we moeten de offset dus opsplitsen in 2 stukken. dit 
	doen we met bitwise operations. 
	
	IDT[number].low_offset = (offset & 0xFFFF);
		hier gebruiken we een bitwise AND om het lage gedeelte eruit te filteren.
		dit werkt als volgt. 
		0xFFFF is deelbaar door 0xFFFF (=1). net als 0x1FFFF (=2) en 0x2FFFF (=3) enz..
		echter, als we nu 0xp2FFAA nemen,  is dat niet deelbaar door 0xFFFF (=2 en een 
		beetje), je houdt wat over. 
		aangezien offset een Dword is, en 0xFFFF een word, blijven de lage 16 bits over. 
		want de als de lage 16 bits 0xFFFF zijn, dan is de offset deelbaar door 0xFFFF. 
		met een and operation houd deelt hij de offset door 0xFFFF, en wat er overblijft
		geeft ie terug als resultaat. 
	IDT[number].high_offset = (offset >> 16);
		hier gebruiken we byteshifting om aan ons antwoord te komen.  we hebben een dword,
		van 32 bits,  en we willen de 16 hoge bits weten. dan schuiven we elke bit 16 
		plaatsen op. bit 1, wordt dus bit -15. enz... bit 17, wordt bit 1, bit 18, wordt 
		bit  2, enz...   we hebben dus de 16 hoge bits, op de lagere 16 bits gezet, en we
		hebben dus de high_offset.
*/
	IDT[number].low_offset = (offset & 0xFFFF);
	IDT[number].selector = selector;
	IDT[number].settings = settings;
	IDT[number].high_offset = (offset >> 16);
}


void loadidt(){	
	idtr IDTR;	/*de IDT descriptor. */
	
	IDTR.limit = (unsigned short)256*(sizeof(struct _interrupt)-1);
	IDTR.base = IDT;
	
	asm volatile("LIDT (%0)": :"p" (&IDTR));
}

void loadexceptions(){
	addint(0, isr00,0);		//zero divide (fault)
	addint(1, isr01,0);		//debug/single step
	addint(2, isr02,0);		//non-maskable interrupt (trap)
	addint(3, isr03,0);		//INT3 (trap)
	addint(4, isr04,0);		//INTO (trap)
	addint(5, isr05,0);		//BOUND (fault)
	addint(6, isr06,0);		//invalid opcode (fault)
	addint(7, isr07,0);		//coprocessor not available (fault)
	addint(8, isr08,0);		//double fault (abort w/ error code)
	addint(9, isr09,0);		//coproc segment overrun (abort; 386/486SX only)
	addint(10, isr10,0);	//bad TSS (fault w/ error code)
	addint(11, isr11,0);	//segment not present (fault w/ error code)
	addint(12, isr12,0);	//stack fault (fault w/ error code)
	addint(13, isr13,0);	//GPF (fault w/ error code)
	addint(14, isr14,0);	//page fault
	addint(15, 0,0);		//reserved by Intel
	addint(16, isr16,0);	//FP exception/coprocessor error (trap)
	addint(17, isr17,0);	//alignment check (trap; 486+ only)
	addint(18, isr18,0);	//machine check (Pentium+ only)
	addint(19, 0,0);
	addint(20, 0,0); 
	addint(21, 0,0);
	addint(22, 0,0);		// interrupts 19 to 31 are reserved by intel.
	addint(23, 0,0);
	addint(24, 0,0);
	addint(25, 0,0);
	addint(26, 0,0);
	addint(27, 0,0);
	addint(28, 0,0);
	addint(29, 0,0);
	addint(30, 0,0);
	addint(31, 0,0);
}
