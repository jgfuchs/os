/*
    interface to the Programmable Interrupt Controller(s)
    the PICs connect the 16 IRQs to the interrupt/ISR system
*/

#ifndef _PIC_H_
#define _PIC_H_

#include <types.h>

// new IRQ offsets
#define PIC1_VOFF 32
#define PIC2_VOFF 40

// IRQ interrupt numbers
#define IRQ_00 32
#define IRQ_01 33
#define IRQ_02 34
#define IRQ_03 35
#define IRQ_04 36
#define IRQ_05 37
#define IRQ_06 38
#define IRQ_07 39
#define IRQ_08 40
#define IRQ_09 41
#define IRQ_10 42
#define IRQ_11 43
#define IRQ_12 44
#define IRQ_13 45
#define IRQ_14 46
#define IRQ_15 47

// is ISR number an IRQ?
#define IS_IRQ(x) ((x >= IRQ_00) && (x <= IRQ_15))

// disable all IRQs
void pic_disable();

// enable all IRQs
void pic_enable();

// block a certain irq
void pic_block(u8 irq);

// unblock an irq
void pic_unblock(u8 irq);

// send end-of-interrupt signal
void pic_eoi(u8 irq);

// change vector offsets
void pic_remap(u8 p1, u8 p2);

#endif  //_PIC_H_
