;;
;;	loads the GDT and IDT
;;

global gdt_load
global idt_load

; argument is pointer to gdt_desc
gdt_load:
	mov eax, [esp + 4]
	lgdt [eax]

	jmp 0x08:.flush

.flush:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	ret

; argument is pointer to idt_desc
idt_load:
	mov eax, [esp + 4]
	lidt [eax]
	ret
