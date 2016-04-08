/*
    VGA interface
    only text mode, only 80 * 25 chars
*/

#ifndef _VGA_H_
#define _VGA_H_

#include <types.h>

#define VGA_COLS 80
#define VGA_ROWS 25

#define VGA_MEM ((u8 *)0xB8000)

// convert (row, col) to linear location
#define VGA_LOC(r, c) ((r)*VGA_COLS + (c))

// colors
// clang-format off
#define VGA_BLACK		0
#define VGA_BLUE		1
#define VGA_GREEN		2
#define VGA_CYAN		3
#define VGA_RED			4
#define VGA_MAGENTA		5
#define VGA_BROWN		6
#define VGA_LGRAY		7
#define VGA_DGRAY		8
#define VGA_LBLUE		9
#define VGA_LGREEN		10
#define VGA_LCYAN		11
#define VGA_LRED		12
#define VGA_LMAGENTA 	13
#define VGA_YELLOW		14
#define VGA_WHITE		15
// clang-format on

// set a character value
static inline void vga_set(u16 loc, char ch, u8 attr) {
    loc *= 2;
    VGA_MEM[loc] = ch;
    VGA_MEM[loc + 1] = attr;
}

// get a character value
static inline void vga_get(u16 loc, char *ch, u8 *attr) {
    loc *= 2;
    *ch = VGA_MEM[loc];
    *attr = VGA_MEM[loc + 1];
}

// set cursor location
void vga_setcursor(u16 r, u16 c);

#undef VGA_MEM

#endif  //_VGA_H_
