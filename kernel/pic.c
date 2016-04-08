/*
    interface to the Programmable Interrupt Controller(s)
*/

#include <bitops.h>
#include <pic.h>
#include <portio.h>

// command & data ports
#define PIC1_CMD 0x20
#define PIC2_CMD 0xA0
#define PIC1_DAT (PIC1_CMD + 1)
#define PIC2_DAT (PIC2_CMD + 1)

// control words
#define ICW1 0x11
#define ICW4 0x01

// end-of-interrupt byte
#define EOI 0x20

// disable all IRQs
void pic_disable() {
    port_outb(PIC1_DAT, 0xff);
    port_outb(PIC2_DAT, 0xff);
}

// enable all IRQs
void pic_enable() {
    port_outb(PIC1_DAT, 0x00);
    port_outb(PIC2_DAT, 0x00);
}

// block a certain irq
void pic_block(u8 irq) {
    u16 port;
    if (irq < 8) {
        port = PIC1_DAT;
    } else {
        port = PIC2_DAT;
        irq -= 8;
    }

    u8 cur = port_inb(port);
    cur |= BIT(irq);
    port_outb(port, cur);
}

// unblock an irq
void pic_unblock(u8 irq) {
    u16 port;
    if (irq < 8) {
        port = PIC1_DAT;
    } else {
        port = PIC2_DAT;
        irq -= 8;
    }

    u8 cur = port_inb(port);
    cur &= ~BIT(irq);
    port_outb(port, cur);
}

// send end-of-interrupt signal
void pic_eoi(u8 irq) {
    if (irq >= 8) {
        port_outb(PIC2_CMD, EOI);
    }

    port_outb(PIC1_CMD, EOI);
}

// change vector offsets
void pic_remap(u8 p1, u8 p2) {
    // save masks
    u8 m1 = port_inb(PIC1_DAT);
    u8 m2 = port_inb(PIC2_DAT);

    // start initialization
    port_outb(PIC1_CMD, ICW1);
    port_outb(PIC2_CMD, ICW1);

    // remap
    port_outb(PIC1_DAT, p1);
    port_outb(PIC2_DAT, p2);

    // config
    port_outb(PIC1_DAT, 4);
    port_outb(PIC2_DAT, 2);

    // finish
    port_outb(PIC1_DAT, ICW4);
    port_outb(PIC2_DAT, ICW4);

    // restore masks
    port_outb(PIC1_DAT, m1);
    port_outb(PIC2_DAT, m2);
}
