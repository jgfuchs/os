;;
;;	access control registers
;;

global get_cr0
global set_cr0

global get_cr2
global set_cr2

global get_cr3
global set_cr3

;machine status word

get_cr0:
	mov eax, cr0
	ret

set_cr0:
	mov eax, [esp + 8]
	mov cr0, eax
	ret

;page fault address

get_cr2:
	mov eax, cr2
	ret

set_cr2:
	mov eax, [esp + 8]
	mov cr2, eax
	ret

;current page directory

get_cr3:
	mov eax, cr3
	ret

set_cr3:
	mov eax, [esp + 8]
	mov cr3, eax
	ret
