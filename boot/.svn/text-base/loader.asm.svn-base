; A loader for the Gabriel kernel
; written by Michiel Tukker. 2006

[BITS 32]
[global _loader]	; the linker needs to see this one.
[extern _main]		

; setting up the Multiboot header 
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
CHECKSUM    equ  -(MAGIC + FLAGS)       ; checksum required

align 4
multiboot_header:
        dd MAGIC
        dd FLAGS
        dd CHECKSUM


_loader:
; We want to enable paging when we're in the kernel, so we'll 
; use the GDT trick from Tim Robinson to translate between our
; physical address (0x100000) and our logical address (0xC0000000)
	lgdt [trickgdt]
	
	mov dx, 0x10
	mov ds, dx
	mov es, dx
	mov fs, dx
	mov gs, dx
	mov ss, dx
	jmp 0x08:high

high:
	; the CPU willt translate everything from now on
	mov esp, sysstack
	push eax	; multiboot magic number
	push ebx	; multiboot structure. this could be anywhere in memory!
	
	cli		; disable interrupts
	call _main	; jump to the kernel
	hlt


; a simple function to load a new gdt. we'll need this after 
; we've enabled paging to load a new gdt.

[global gdt_flush]
[extern gp]			
gdt_flush:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2

flush2:
	ret



[section .setup] 

trickgdt:
        dw gdt_end - gdt - 1 
        dd gdt 

gdt:
nullsel:
        dd 0, 0                                                 ; null gate
codesel:
        db 0xFF, 0xFF, 0, 0, 0, 10011010b, 11001111b, 0x40      ; code selector 0x08: base 0x40000000, limit 0xFFFFFFFF, type 0x9A, granularity 0xCF
datasel:
        db 0xFF, 0xFF, 0, 0, 0, 10010010b, 11001111b, 0x40      ; data selector 0x10: base 0x40000000, limit 0xFFFFFFFF, type 0x92, granularity 0xCF

gdt_end:

[section .bss]

resb 0x1000
sysstack:
		
;the kernel stack.
