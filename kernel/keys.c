#include <keys.h>
#include <types.h>

/* clang-format off */

const struct key_ascii key_ascii_table[KEY__MAX] = {
	[KEY_TICK] = {'`', '~'},		[KEY_1] = {'1', '!'},
	[KEY_2] = {'2', '@'},			[KEY_3] = {'3', '#'},
	[KEY_4] = {'4', '$'},			[KEY_5] = {'5', '%'},
	[KEY_6] = {'6', '^'},			[KEY_7] = {'7', '&'},
	[KEY_8] = {'8', '*'},			[KEY_9] = {'9', '('},
	[KEY_0] = {'0', ')'},			[KEY_MINUS] = {'-', '_'},
	[KEY_EQUALS] = {'=', '+'},		[KEY_TAB] = {'\t', '\t'},
	[KEY_Q] = {'q', 'Q'},			[KEY_W] = {'w', 'W'},
	[KEY_E] = {'e', 'E'},			[KEY_R] = {'r', 'R'},
	[KEY_T] = {'t', 'T'},			[KEY_Y] = {'y', 'Y'},
	[KEY_U] = {'u', 'U'},			[KEY_I] = {'i', 'I'},
	[KEY_O] = {'o', 'O'},			[KEY_P] = {'p', 'P'},
	[KEY_LBRACK] = {'[', '{'},		[KEY_RBRACK] = {']', '}'},
	[KEY_BKSLASH] = {'\\', '|'},	[KEY_A] = {'a', 'A'},
	[KEY_S] = {'s', 'S'},			[KEY_D] = {'d', 'D'},
	[KEY_F] = {'f', 'F'},			[KEY_G] = {'g', 'G'},
	[KEY_H] = {'h', 'H'},			[KEY_J] = {'j', 'J'},
	[KEY_K] = {'k', 'K'},			[KEY_L] = {'l', 'L'},
	[KEY_SEMICOLON] = {';', ':'},	[KEY_APOST] = {'\'', '"'},
	[KEY_ENTER] = {'\n', '\n'},		[KEY_Z] = {'z', 'Z'},
	[KEY_X] = {'x', 'X'},			[KEY_C] = {'c', 'C'},
	[KEY_V] = {'v', 'V'},			[KEY_B] = {'b', 'B'},
	[KEY_N] = {'n', 'N'},			[KEY_M] = {'m', 'M'},
	[KEY_COMMA] = {',', '<'},		[KEY_PERIOD] = {'.', '>'},
	[KEY_SLASH] = {'/', '?'},		[KEY_SPACE] = {' ', ' '},
};

const char *key_string_table[KEY__MAX] = {
	[KEY_NONE] = "KEY_NONE",			[KEY_ESC] = "KEY_ESC",
	[KEY_F1] = "KEY_F1",				[KEY_F2] = "KEY_F2",
	[KEY_F3] = "KEY_F3",				[KEY_F4] = "KEY_F4",
	[KEY_F5] = "KEY_F5",				[KEY_F6] = "KEY_F6",
	[KEY_F7] = "KEY_F7",				[KEY_F8] = "KEY_F8",
	[KEY_F9] = "KEY_F9",				[KEY_F10] = "KEY_F10",
	[KEY_F11] = "KEY_F11",				[KEY_F12] = "KEY_F12",
	[KEY_HOME] = "KEY_HOME",			[KEY_END] = "KEY_END",
	[KEY_INSERT] = "KEY_INSERT",		[KEY_DELETE] = "KEY_DELETE",
	[KEY_TICK] = "KEY_TICK",			[KEY_1] = "KEY_1",
	[KEY_2] = "KEY_2",					[KEY_3] = "KEY_3",
	[KEY_4] = "KEY_4",					[KEY_5] = "KEY_5",
	[KEY_6] = "KEY_6",					[KEY_7] = "KEY_7",
	[KEY_8] = "KEY_8",					[KEY_9] = "KEY_9",
	[KEY_0] = "KEY_0",					[KEY_MINUS] = "KEY_MINUS",
	[KEY_EQUALS] = "KEY_EQUALS",		[KEY_BACKSPACE] = "KEY_BACKSPACE",
	[KEY_TAB] = "KEY_TAB",				[KEY_Q] = "KEY_Q",
	[KEY_W] = "KEY_W",					[KEY_E] = "KEY_E",
	[KEY_R] = "KEY_R",					[KEY_T] = "KEY_T",
	[KEY_Y] = "KEY_Y",					[KEY_U] = "KEY_U",
	[KEY_I] = "KEY_I",					[KEY_O] = "KEY_O",
	[KEY_P] = "KEY_P",					[KEY_LBRACK] = "KEY_LBRACK",
	[KEY_RBRACK] = "KEY_RBRACK",		[KEY_BKSLASH] = "KEY_BKSLASH",
	[KEY_CAPS] = "KEY_CAPS",			[KEY_A] = "KEY_A",
	[KEY_S] = "KEY_S",					[KEY_D] = "KEY_D",
	[KEY_F] = "KEY_F",					[KEY_G] = "KEY_G",
	[KEY_H] = "KEY_H",					[KEY_J] = "KEY_J",
	[KEY_K] = "KEY_K",					[KEY_L] = "KEY_L",
	[KEY_SEMICOLON] = "KEY_SEMICOLON",	[KEY_APOST] = "KEY_APOST",
	[KEY_ENTER] = "KEY_ENTER",			[KEY_LSHIFT] = "KEY_LSHIFT",
	[KEY_Z] = "KEY_Z",					[KEY_X] = "KEY_X",
	[KEY_C] = "KEY_C",					[KEY_V] = "KEY_V",
	[KEY_B] = "KEY_B",					[KEY_N] = "KEY_N",
	[KEY_M] = "KEY_M",					[KEY_COMMA] = "KEY_COMMA",
	[KEY_PERIOD] = "KEY_PERIOD",		[KEY_SLASH] = "KEY_SLASH",
	[KEY_RSHIFT] = "KEY_RSHIFT",		[KEY_LCTRL] = "KEY_LCTRL",
	[KEY_LWINDOWS] = "KEY_LWINDOWS",	[KEY_LALT] = "KEY_LALT",
	[KEY_SPACE] = "KEY_SPACE",			[KEY_RALT] = "KEY_RALT",
	[KEY_RCTRL] = "KEY_RCTRL",			[KEY_RWINDOWS] = "KEY_RWINDOWS",
	[KEY_PGUP] = "KEY_PGUP",			[KEY_PGDOWN] = "KEY_PGDOWN",
	[KEY_UARROW] = "KEY_UARROW",		[KEY_LARROW] = "KEY_LARROW",
	[KEY_DARROW] = "KEY_DARROW",		[KEY_RARROW] = "KEY_RARROW",
	[KEY_SCROLLOCK] = "KEY_SCROLLOCK",	[KEY_NUMLOCK] = "KEY_NUMLOCK",
	[KEY_KPSLASH] = "KEY_KPSLASH",		[KEY_KPSTAR] = "KEY_KPSTAR",
	[KEY_KPMINUS] = "KEY_KPMINUS",		[KEY_KPPLUS] = "KEY_KPPLUS",
	[KEY_KPENTER] = "KEY_KPENTER",		[KEY_KPDOT] = "KEY_KPDOT",
	[KEY_KP0] = "KEY_KP0",				[KEY_KP1] = "KEY_KP1",
	[KEY_KP2] = "KEY_KP2",				[KEY_KP3] = "KEY_KP3",
	[KEY_KP4] = "KEY_KP4",				[KEY_KP5] = "KEY_KP5",
	[KEY_KP6] = "KEY_KP6",				[KEY_KP7] = "KEY_KP7",
	[KEY_KP8] = "KEY_KP8",				[KEY_KP9] = "KEY_KP9",
	[KEY_POWER] = "KEY_POWER",			[KEY_SLEEP] = "KEY_SLEEP",
	[KEY_WAKE] = "KEY_WAKE",			[KEY_MENU] = "KEY_MENU",
	[KEY_NEXT] = "KEY_NEXT",			[KEY_PREV] = "KEY_PREV",
	[KEY_STOP] = "KEY_STOP",			[KEY_PLAY] = "KEY_PLAY",
	[KEY_MUTE] = "KEY_MUTE",			[KEY_VOLUP] = "KEY_VOLUP",
	[KEY_VOLDOWN] = "KEY_VOLDOWN"
};
