;-----------------------------
; Macro's that'll setup our
; interrupt handlers
;-----------------------------
extern _int_handler

%macro INTR 1
extern _int_handler
[global isr%1]
isr%1:	
		push %1
		mov eax, _int_handler
		call eax;
		pop eax
		nop
		iret
%endmacro

%macro INTR_EC 1
extern _int_handler
[global isr%1]
isr%1:
	
		push %1
		mov eax, _int_handler
		call eax;
		pop eax
		pop eax
		iret
%endmacro


INTR 00      ;zero divide (fault)
INTR 01      ;debug/single step
INTR 02      ;non-maskable interrupt (trap)
INTR 03      ;INT3 (trap)
INTR 04      ;INTO (trap)
INTR 05      ;BOUND (fault)
INTR 06      ;invalid opcode (fault)
INTR 07      ;coprocessor not available (fault)
INTR_EC 08	 ;double fault (abort w/ error code)
INTR 09      ;coproc segment overrun (abort; 386/486SX only)
INTR_EC 10	;bad TSS (fault w/ error code)
INTR_EC 11	;segment not present (fault w/ error code)
INTR_EC 12	;stack fault (fault w/ error code)
INTR_EC 13	;GPF (fault w/ error code)
INTR_EC 14	;page fault
INTR 15		;reserved
INTR 16		;FP exception/coprocessor error (trap)
INTR 17		;alignment check (trap; 486+ only)
INTR 18		;machine check (Pentium+ only)
INTR 19
INTR 20
INTR 21
INTR 22
INTR 23
INTR 24
INTR 25
INTR 26
INTR 27
INTR 28
INTR 29
INTR 30
INTR 31

INTR 32    ;IRQ 0/timer interrupt
INTR 33    ;IRQ 1/keyboard interrupt
INTR 34
INTR 35
INTR 36
INTR 37
INTR 38    ;IRQ 6/floppy interrupt
INTR 39
INTR 40    ;IRQ 8/real-time clock interrupt
INTR 41
INTR 42
INTR 43
INTR 44
INTR 45    ;IRQ 13/math coprocessor interrupt
INTR 46    ;IRQ 14/primary ATA ("IDE") drive interrupt
INTR 47    ;IRQ 15/secondary ATA drive interrupt
INTR 48

; the other 207 vectors are undefined
%assign i 31h
%rep (0FFh - 30h)
	INTR i
%assign i (i + 1)
%endrep
