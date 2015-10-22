;;
;;	entry point from bootloader
;;

; multiboot constants
MAGIC equ 0x1BADB002
MFLAG equ (1 | 2)

; multiboot header
align 4

dd MAGIC
dd MFLAG
dd -(MAGIC + MFLAG)

; 8 kb stack for now
STACKSIZE equ 0x2000

global start

extern kmain

start:
	;set stack
	mov esp, (stack + STACKSIZE)

	;clear flags
	push 0
	popf

	;go to kernel
	push ebx
	push eax
	call kmain

	;hang
	cli
	hlt


section .bss
	align 4
	stack: resb STACKSIZE
