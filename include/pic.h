/*
	interface to the Programmable Interrupt Controller(s)
	the PICs connect the 16 IRQs to the interrupt/ISR system
*/

#ifndef _PIC_H_
#define _PIC_H_

#include <types.h>

//	new IRQ offsets
#define PIC1_VOFF	32
#define PIC2_VOFF	40

//	IRQ interrupt numbers
#define IRQ0	32
#define IRQ1	33
#define IRQ2	34
#define IRQ3	35
#define IRQ4	36
#define IRQ5	37
#define IRQ6	38
#define IRQ7	39
#define IRQ8	40
#define IRQ9	41
#define IRQ10	42
#define IRQ11	43
#define IRQ12	44
#define IRQ13	45
#define IRQ14	46
#define IRQ15	47

//	is ISR number an IRQ?
#define IS_IRQ(x) ((x >= IRQ0) && (x <= IRQ15))

//	disable all IRQs
void pic_disable();

//	enable all IRQs
void pic_enable();

//	block a certain irq
void pic_block(u8 irq);

//	unblock an irq
void pic_unblock(u8 irq);

//	send end-of-interrupt signal
void pic_eoi(u8 irq);

//	change vector offsets
void pic_remap(u8 p1, u8 p2);

#endif //_PIC_H_
