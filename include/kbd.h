/*
	PS/2 keyboard driver

	interfaces with the keyboard encoder (Intel 8048, port 0x60),
	and the keyboard controller (Intel 8042, port 0x64)
*/

#ifndef _KBD_H_
#define _KBD_H_

#include <keys.h>

struct kbd_event {
	int keycode;
	int state;
};

//	keyboard event callback signature
typedef void (*kbd_event_f)(struct kbd_event);

//	initialize keyboard
void kbd_init();

//	control keyboard LEDs
void kbd_set_leds(int scroll, int num, int caps);

//	set what function gets called for keyboard events
void kbd_set_callback(kbd_event_f func);

#endif //_KBD_H_
