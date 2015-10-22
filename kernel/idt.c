/*
	Interrupt Descriptor Table setup
*/

#include <idt.h>
#include <pic.h>
#include <types.h>

//	assembly in dt_load.asm
extern void idt_load(u32);

//	segment selector
#define IDT_SEL		0x08

//	flags byte
#define IDT_PRES(x)	((x) << 7)
#define IDT_PRIV(x) ((x) << 5)
#define IDT_STOR(x) ((x) << 4)

//	the various IDT entry types
#define IDT_TASK32	0x5
#define IDT_INT16	0x6
#define IDT_TRAP16	0x7
#define IDT_INT32	0xE
#define IDT_TRAP32	0xF

//	all use the same value
#define IDT_FLAGS	(IDT_PRES(1) | IDT_PRIV(0) | IDT_STOR(0) | IDT_INT32)

//	one interrupt descriptor
struct idt_entry {
	u16 addr_l;
	u16 selector;
	u8 _unused;
	u8 flags;
	u16 addr_h;
} __attribute__ ((packed));

//	pointer to the IDT
struct idt_desc {
	u16 size;
	u32 addr;
} __attribute__ ((packed));

//	the IDT itself
struct idt_entry idt[256];

//	pointer used with LIDT
struct idt_desc idtr;

//	create one interrupt descriptor
static void idt_create(int ind, u32 base, u16 selec, u8 flags) {
	struct idt_entry *i = &idt[ind];
	i->addr_l = base & 0xFFFF;
	i->addr_h = (base >> 16) & 0xFFFF;
	i->selector = selec;
	i->_unused = 0;
	i->flags = flags;
}

//	ISRs in isr_stubs.s
#define ISR(x)	extern void isr##x (); \
				idt_create(x, (u32) isr##x, IDT_SEL, IDT_FLAGS)

//	IRQ handlers in isr_stubs.s
#define IRQ(x)	extern void irq##x (); \
				idt_create(x + PIC1_VOFF, (u32) irq##x, IDT_SEL, IDT_FLAGS)

void idt_init() {
	//	ISRs 0-31: exceptions
	ISR(0);
	ISR(1);
	ISR(2);
	ISR(3);
	ISR(4);
	ISR(5);
	ISR(6);
	ISR(7);
	ISR(8);
	ISR(9);
	ISR(10);
	ISR(11);
	ISR(12);
	ISR(13);
	ISR(14);
	ISR(15);
	ISR(16);
	ISR(17);
	ISR(18);
	ISR(19);
	ISR(20);
	ISR(21);
	ISR(22);
	ISR(23);
	ISR(24);
	ISR(25);
	ISR(26);
	ISR(27);
	ISR(28);
	ISR(29);
	ISR(30);
	ISR(31);

	//	change IRQ offsets to avoid collisions
	pic_remap(PIC1_VOFF, PIC2_VOFF);

	//	ISRs 32-47 are IRQs
	IRQ(0);
	IRQ(1);
	IRQ(2);
	IRQ(3);
	IRQ(4);
	IRQ(5);
	IRQ(6);
	IRQ(7);
	IRQ(8);
	IRQ(9);
	IRQ(10);
	IRQ(11);
	IRQ(12);
	IRQ(13);
	IRQ(14);
	IRQ(15);

	idtr.size = sizeof(struct idt_entry) * 256 - 1;
	idtr.addr = (u32) &idt;

	idt_load((u32) &idtr);
}
