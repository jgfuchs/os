/*
    wrappers for IN and OUT instructions for hardware port I/O
*/

#ifndef _PORTIO_H_
#define _PORTIO_H_

#include <types.h>

static inline u8 port_inb(u16 port) {
    u8 val;
    asm volatile("inb %1, %0" : "=a"(val) : "dN"(port));
    return val;
}

static inline void port_outb(u16 port, u8 val) {
    asm volatile("outb %0, %1" : : "a"(val), "dN"(port));
}

static inline u16 port_inw(u16 port) {
    u16 val;
    asm volatile("inw %1, %0" : "=a"(val) : "dN"(port));
    return val;
}

static inline void port_outw(u16 port, u16 val) {
    asm volatile("outw %0, %1" : : "a"(val), "dN"(port));
}

static inline u32 port_ind(u16 port) {
    u32 val;
    asm volatile("ind %1, %0" : "=a"(val) : "dN"(port));
    return val;
}

static inline void port_outd(u16 port, u32 val) {
    asm volatile("outd %0, %1" : : "a"(val), "dN"(port));
}

#endif  //_PORTIO_H_
