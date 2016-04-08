#include <con.h>

#include <vga.h>

u8 con_attr;

// initialize console
void con_init() {
    con_setfg(VGA_LGRAY);
    con_setbg(VGA_BLACK);
    con_clear();
    vga_setcursor(0, 0);
}

void con_clear() {
    u16 loc;
    for (loc = 0; loc < (VGA_ROWS * VGA_COLS); loc++) {
        vga_set(loc, ' ', con_attr);
    }
}

// scroll up one
static void con_scroll() {
    u16 loc;

    // copy first 24 lines up one line
    const int first24 = (VGA_ROWS - 1) * VGA_COLS;
    for (loc = 0; loc < first24; loc++) {
        char ch;
        u8 attr;

        vga_get(loc + VGA_COLS, &ch, &attr);
        vga_set(loc, ch, attr);
    }

    // blank out bottom line
    for (loc = first24; loc < VGA_ROWS * VGA_COLS; loc++) {
        vga_set(loc, ' ', con_attr);
    }
}

// print a character
void con_putc(char ch) {
    // row (y axis)
    static u16 cursor_r = 0;

    // column (x axis)
    static u16 cursor_c = 0;

    switch (ch) {
        case '\n':
            cursor_c = 0;
            cursor_r++;
            break;
        case '\t':
            cursor_c = (cursor_c + 8) & ~7;
            break;
        case '\b':
            if (cursor_c) {
                cursor_c--;
                vga_set(VGA_LOC(cursor_r, cursor_c), ' ', con_attr);
            }
            break;
        default:
            vga_set(VGA_LOC(cursor_r, cursor_c), ch, con_attr);
            cursor_c++;
            break;
    }

    // newline?
    if (cursor_c == VGA_COLS) {
        cursor_c = 0;
        cursor_r++;
    }

    // scroll?
    if (cursor_r == VGA_ROWS) {
        con_scroll();
        cursor_r--;
    }

    vga_setcursor(cursor_r, cursor_c);
}
