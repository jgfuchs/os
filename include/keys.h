/*
    codes for every keyboard key, and functions to convert them to ASCII
*/

#ifndef _KEYS_H_
#define _KEYS_H_

#include <cclass.h>

// keycodes, assigned roughly top-left to bottom-right across the keyboard, with
// all the keys that aren't on my keyboard just put at the end

// clang-format off
#define KEY_NONE		0
#define KEY_ESC			1
#define KEY_F1			2
#define KEY_F2			3
#define KEY_F3			4
#define KEY_F4			5
#define KEY_F5			6
#define KEY_F6			7
#define KEY_F7			8
#define KEY_F8			9
#define KEY_F9			10
#define KEY_F10			11
#define KEY_F11			12
#define KEY_F12			13
#define KEY_HOME		14
#define KEY_END			15
#define KEY_INSERT		16
#define KEY_DELETE		17
#define KEY_TICK		18
#define KEY_1			19
#define KEY_2			20
#define KEY_3			21
#define KEY_4			22
#define KEY_5			23
#define KEY_6			24
#define KEY_7			25
#define KEY_8			26
#define KEY_9			27
#define KEY_0			28
#define KEY_MINUS		29
#define KEY_EQUALS		30
#define KEY_BACKSPACE	31
#define KEY_TAB			32
#define KEY_Q			33
#define KEY_W			34
#define KEY_E			35
#define KEY_R			36
#define KEY_T			37
#define KEY_Y			38
#define KEY_U			39
#define KEY_I			40
#define KEY_O			41
#define KEY_P			42
#define KEY_LBRACK		43
#define KEY_RBRACK		44
#define KEY_BKSLASH		45
#define KEY_CAPS		46
#define KEY_A			47
#define KEY_S			48
#define KEY_D			49
#define KEY_F			50
#define KEY_G			51
#define KEY_H			52
#define KEY_J			53
#define KEY_K			54
#define KEY_L			55
#define KEY_SEMICOLON	56
#define KEY_APOST		57
#define KEY_ENTER		58
#define KEY_LSHIFT		59
#define KEY_Z			60
#define KEY_X			61
#define KEY_C			62
#define KEY_V			63
#define KEY_B			64
#define KEY_N			65
#define KEY_M			66
#define KEY_COMMA		67
#define KEY_PERIOD		68
#define KEY_SLASH		69
#define KEY_RSHIFT		70
#define KEY_LCTRL		71
#define KEY_LWINDOWS	72
#define KEY_LALT		73
#define KEY_SPACE		74
#define KEY_RALT		75
#define KEY_RCTRL		76
#define KEY_RWINDOWS	77
#define KEY_PGUP		78
#define KEY_PGDOWN		79
#define KEY_UARROW		80
#define KEY_LARROW		81
#define KEY_DARROW		82
#define KEY_RARROW		83
#define KEY_SCROLLOCK	84
#define KEY_NUMLOCK		85
#define KEY_KPSLASH		86		//keypad
#define KEY_KPSTAR		87
#define KEY_KPMINUS		88
#define KEY_KPPLUS		89
#define KEY_KPENTER		90
#define KEY_KPDOT		91
#define KEY_KP0			92
#define KEY_KP1			93
#define KEY_KP2			94
#define KEY_KP3			95
#define KEY_KP4			96
#define KEY_KP5			97
#define KEY_KP6			98
#define KEY_KP7			99
#define KEY_KP8			100
#define KEY_KP9			101
#define KEY_POWER		102		//ACPI
#define KEY_SLEEP		103
#define KEY_WAKE		104
#define KEY_MENU		105		//media
#define KEY_NEXT		106
#define KEY_PREV		107
#define KEY_STOP		108
#define KEY_PLAY		109
#define KEY_MUTE		110
#define KEY_VOLUP		111
#define KEY_VOLDOWN		112

#define KEY__MAX		128		//approximately

#define KEY__UP			1
#define KEY__DOWN		2
// clang-format on

struct key_ascii {
    char normal;
    char shifted;
};

static inline char key_to_ascii(int keycode, int shift) {
    extern const struct key_ascii key_ascii_table[KEY__MAX];
    if (keycode < KEY__MAX) {
        struct key_ascii ka = key_ascii_table[keycode];
        return shift ? ka.shifted : ka.normal;
    } else {
        return 0;
    }
}

static inline const char *key_to_string(int keycode) {
    extern const char *key_string_table[KEY__MAX];
    if (keycode < KEY__MAX) {
        return key_string_table[keycode];
    } else {
        return NULL;
    }
}

#endif  //_KEYS_H_
