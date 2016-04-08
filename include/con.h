/*
    console functions
*/

#ifndef _CON_H_
#define _CON_H_

#include <types.h>
#include <vga.h>

extern u8 con_attr;

// initialize console
void con_init();

// write spaces to every screen location
void con_clear();

// print a character
void con_putc(char ch);

// print a string
static inline void con_puts(char *msg) {
    while (*msg)
        con_putc(*msg++);
}

static inline void con_setfg(u8 fg) {
    con_attr &= 0xF0;
    con_attr |= fg & 0x0F;
}

static inline void con_setbg(u8 bg) {
    con_attr &= 0x0F;
    con_attr |= bg << 4;
}

static inline u8 con_getfg() {
    return con_attr & 0x0F;
}

static inline u8 con_getbg() {
    return con_attr >> 4;
}

#endif  //_CON_H_
