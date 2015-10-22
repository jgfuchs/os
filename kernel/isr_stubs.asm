;;
;;	Interrupt Service Request stubs
;;	all ISRs (and IRQs) jump to isr_stub, which calls isr_handle in isr.c
;;

;	in isr.c
extern isr_handle

isr_stub:
	pusha

	;save data segment
	mov ax, ds
	push eax

	;kernel data
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov fs, ax

	call isr_handle

	;restore data segment
	pop eax
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov fs, ax

	popa

	;clear off int # and (maybe) error code
	add esp, 8

	sti
	iret

;	no error code
%macro ISR_NOCODE 1
	global isr%1
	isr%1:
		cli
		push 0
		push %1
		jmp isr_stub
%endmacro

;	a sequence of NOCODEs
%macro ISR_NOCODES 2
	%assign i %1
	%rep %2 - %1 + 1
		ISR_NOCODE i
		%assign i i+1
	%endrep
%endmacro

;	some interrupts also push an error code
%macro ISR_CODE 1
	global isr%1
	isr%1:
		cli
		push %1
		jmp isr_stub
%endmacro

;	ISRs 0-31: exceptions
ISR_NOCODES 0, 7
ISR_CODE 8
ISR_NOCODE 9
ISR_CODE 10
ISR_CODE 11
ISR_CODE 12
ISR_CODE 13
ISR_CODE 14
ISR_NOCODES 15, 31

;	ISRs 32-47: IRQs
%assign i 0
%rep 16
	global irq %+ i
	irq %+ i:
		cli
		push 0
		push i + 32
		jmp isr_stub
	%assign i i+1
%endrep

;	ISRs 48-255: unused so far
;ISR_NOCODES 48, 255
