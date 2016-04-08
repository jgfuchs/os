/*
    Rudimentary terminal
*/

#include <con.h>
#include <kbd.h>
#include <keys.h>
#include <printf.h>
#include <term.h>
#include <timer.h>
#include <types.h>

static char line_buffer[256];

struct {
    uint line_pos;
    u8 processing : 1;
    u8 caps_lock : 1;
    u8 shifted : 2;  // both keys can be pressed at the same time
} state;

// return whether one of the shift keys is down
static inline int term_shift_state() {
    return state.shifted ^ state.caps_lock;
}

// handle key events
void term_key_event(struct kbd_event ev) {
    if (ev.state == KEY__DOWN) {
        char c;
        switch (ev.keycode) {
            case KEY_CAPS:
                state.caps_lock = !state.caps_lock;
                return;
            case KEY_LSHIFT:
            case KEY_RSHIFT:
                state.shifted++;
                return;
            case KEY_BACKSPACE:
                con_putc('\b');
                return;
        }

        c = key_to_ascii(ev.keycode, term_shift_state());
        if (c) {
            con_putc(c);
        }
    } else {
        switch (ev.keycode) {
            case KEY_LSHIFT:
            case KEY_RSHIFT:
                state.shifted--;
        }
    }
}

// initialize and start processing
void term_init() {
    kbd_set_callback(term_key_event);
}

// start "REPL" loop
void term_start() {
    while (1) {
    }
}
