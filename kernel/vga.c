/*
	VGA interface
	only text mode, only 80 * 25 chars
*/

#include <vga.h>
#include <portio.h>

//	controller ports
#define VGA_CTRL	0x3D4
#define VGA_DATA	0x3D5

//	controller regiser
#define VGA_LOC_HIGH	0xE
#define VGA_LOC_LOW		0xF

void vga_setcursor(u16 r, u16 c) {
	u16 loc = r * VGA_COLS + c;
	port_outb(VGA_CTRL, VGA_LOC_HIGH);
	port_outb(VGA_DATA, loc >> 8);
	port_outb(VGA_CTRL, VGA_LOC_LOW);
	port_outb(VGA_DATA, loc & 0xFF);
}

