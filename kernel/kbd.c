/*
	PS/2 keyboard driver

	interfaces with the keyboard encoder (Intel 8048, port 0x60),
	and the keyboard controller (Intel 8042, port 0x64)
*/

#include <kbd.h>

#include <bitops.h>
#include <con.h>
#include <error.h>
#include <isr.h>
#include <keys.h>
#include <panic.h>
#include <pic.h>
#include <portio.h>
#include <printf.h>

//	map scancodes to key codes defined in keys.h
static const int scancode_set2[256] = {
//	0				1				2				3				4				5				6				7
//	8				9				A				B				C				D				E				F
	KEY_NONE,		KEY_F9,			KEY_F7,			KEY_F5,			KEY_F3,			KEY_F1,			KEY_F2,			KEY_F12,		// 00
	KEY_NONE,		KEY_F10,		KEY_F8,			KEY_F6,			KEY_F4,			KEY_TAB,		KEY_TICK,		KEY_NONE,
	KEY_NONE,		KEY_LALT,		KEY_LSHIFT,		KEY_NONE,		KEY_LCTRL,		KEY_Q,			KEY_1,			KEY_NONE,		// 10
	KEY_NONE,		KEY_NONE,		KEY_Z,			KEY_S,			KEY_A,			KEY_W,			KEY_2,			KEY_NONE,
	KEY_NONE,		KEY_C,			KEY_X,			KEY_D,			KEY_E,			KEY_4,			KEY_3,			KEY_NONE,		// 20
	KEY_NONE,		KEY_SPACE,		KEY_V,			KEY_F,			KEY_T,			KEY_R,			KEY_5,			KEY_NONE,
	KEY_NONE,		KEY_N,			KEY_B,			KEY_H,			KEY_G,			KEY_Y,			KEY_6,			KEY_NONE,		// 30
	KEY_NONE,		KEY_NONE,		KEY_M,			KEY_J,			KEY_U,			KEY_7,			KEY_8,			KEY_NONE,
	KEY_NONE,		KEY_COMMA,		KEY_K,			KEY_I,			KEY_O,			KEY_0,			KEY_9,			KEY_NONE,		// 40
	KEY_NONE,		KEY_PERIOD,		KEY_SLASH,		KEY_L,			KEY_SEMICOLON,	KEY_P,			KEY_MINUS,		KEY_NONE,
	KEY_NONE,		KEY_NONE,		KEY_APOST,		KEY_NONE,		KEY_LBRACK,		KEY_EQUALS,		KEY_NONE,		KEY_NONE,		// 50
	KEY_CAPS,		KEY_RSHIFT,		KEY_ENTER,		KEY_RBRACK,		KEY_NONE,		KEY_BKSLASH,	KEY_NONE,		KEY_NONE,
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_BACKSPACE,	KEY_NONE,		// 60
	KEY_NONE,		KEY_KP1,		KEY_NONE,		KEY_KP4,		KEY_KP7,		KEY_NONE,		KEY_NONE,		KEY_NONE,
	KEY_KP0,		KEY_KPDOT,		KEY_KP2,		KEY_KP5,		KEY_KP6,		KEY_KP8,		KEY_ESC,		KEY_NUMLOCK,	// 70
	KEY_F11,		KEY_KPPLUS,		KEY_KP3,		KEY_KPMINUS,	KEY_KPSTAR,		KEY_KP9,		KEY_SCROLLOCK,	KEY_NONE,

	//	2-byte characters -- first byte always 0xE0

	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		// 00
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,
	KEY_NONE,		KEY_RALT,		KEY_NONE,		KEY_NONE,		KEY_RCTRL,		KEY_PREV,		KEY_NONE,		KEY_NONE,		// 10
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_LWINDOWS,
	KEY_NONE,		KEY_VOLDOWN,	KEY_NONE,		KEY_MUTE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_RWINDOWS,	// 20
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_MENU,
	KEY_NONE,		KEY_NONE,		KEY_VOLUP,		KEY_NONE,		KEY_PLAY,		KEY_NONE,		KEY_NONE,		KEY_POWER,		// 30
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_STOP,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_SLEEP,
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		// 40
	KEY_NONE,		KEY_NONE,		KEY_KPSLASH,	KEY_NONE,		KEY_NONE,		KEY_NEXT,		KEY_NONE,		KEY_NONE,
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		// 50
	KEY_NONE,		KEY_NONE,		KEY_KPENTER,	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_WAKE,		KEY_NONE,
	KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		KEY_NONE,		// 60
	KEY_NONE,		KEY_END,		KEY_NONE,		KEY_LARROW,		KEY_HOME,		KEY_NONE,		KEY_NONE,		KEY_NONE,
	KEY_INSERT,		KEY_DELETE,		KEY_DARROW,		KEY_NONE,		KEY_RARROW,		KEY_UARROW,		KEY_NONE,		KEY_NONE,		// 70
	KEY_NONE,		KEY_NONE,		KEY_PGDOWN,		KEY_NONE,		KEY_NONE,		KEY_PGUP,		KEY_NONE,		KEY_NONE,
};

//	encoder & controller ports
#define KBD_ENC				0x60
#define KBD_CTRL			0x64

//	encoder commands (sent to KBD_ENC)
#define KBD_ENC_SETLEDS		0xED
#define KBD_ENC_ECHO		0xEE
#define KBD_ENC_CODESET		0xF0	// set & get the scancode set
#define KBD_ENC_GETID		0xF2
#define KBD_ENC_TYPEMAT		0xF3
#define KBD_ENC_ENABLE		0xF4
#define KBD_ENC_DISABLE		0xF5
#define KBD_ENC_DEFAULT		0xF6
#define KBD_ENC_RESET		0xFF

//	LED flags (sent to encoder after KBD_ENC_SETLEDS)
#define KBD_LEDS_OFF		0
#define KBD_LEDS_SCROLL		BIT(0)
#define KBD_LEDS_NUM		BIT(1)
#define KBD_LEDS_CAPS		BIT(2)

//	encoder responses
#define KBD_RES_ERR			0x00
#define KBD_RES_TESTOK		0xAA
#define KBD_RES_ECHO		0xEE
#define KBD_RES_ACK			0xFA
#define KBD_RES_TESTBAD		0xFC
#define KBD_RES_RESEND		0xFE
#define kBD_RES_KEYERR		0xFF

//	controller status flags (status byte read from port KBD_CTRL)
#define KBD_STAT_OUTBUF		BIT(0)	// outbuf full -- data available
#define KBD_STAT_INBUF		BIT(1)	// inbuf full -- don't write
#define KBD_STAT_WARM		BIT(2)	// same as KBD_CONF_WARM
#define KBD_STAT_LASTCMD	BIT(3) 	// was last input a command?
#define KBD_STAT_NOTLOCKED	BIT(4)	// unlocked
#define KBD_STAT_AUXBUF		BIT(5)	// data is from mouse
#define KBD_STAT_TIMEOUT	BIT(6)
#define KBD_STAT_PARITYERR	BIT(7)

//	controller commands (sent to port KBD_CTRL)
#define KBD_CTRL_GETCONF	0x20	// get & set command/configuration byte,
#define KBD_CTRL_SETCONF	0x60	// bit flags below
#define KBD_CTRL_MOUSEOFF	0xA7
#define KBD_CTRL_MOUSEON	0xA8
#define KBD_CTRL_TESTPORT2	0xA9	// test mouse port
#define KBD_CTRL_SELFTEST	0xAA
#define KBD_CTRL_TESTPORT1	0xAB	// test keyboard port
#define KBD_CTRL_KBDOFF		0xAD
#define KBD_CTRL_KBDON		0xAE
#define KBD_CTRL_RESET		0xFE

//	controller configuration flags
#define KBD_CONF_KBDINTS	BIT(0)	// interrupt IRQ1 for keyboard
#define KBD_CONF_MOUSEINTS	BIT(1)	// interrupt IRQ12 for mouse
#define KBD_CONF_WARM		BIT(2)
#define KBD_CONF_KBDOFF		BIT(4)	// keyboard disabled
#define KBD_CONF_MOUSEOFF	BIT(5)	// mouse disabled
#define KBD_CONF_TRANSLATE	BIT(6)	// translate scancode sets

//	returned by KBD_CTRL_SELFTEST
#define KBD_CTRL_TESTOK		0x55
#define KBD_CTRL_TESTBAD	0xFC

//	keyboard event callback function
kbd_event_f kbd_callback;

union {
	struct {
		u8 isbreak: 1;		// seen 0xE0 code
		u8 escaped: 1;		// seen 0xF0 code
	};
	u8 val;
} kbd_state;

//	read encoder buffer
static inline u8 kbd_enc_read() {
	return port_inb(KBD_ENC);
}

//	get controller status
static inline u8 kbd_ctrl_status() {
	return port_inb(KBD_CTRL);
}

//	is input buffer not full?
static inline int kbd_can_write() {
	return !(kbd_ctrl_status() & KBD_STAT_INBUF);
}

//	is output buffer full?
static inline int kbd_can_read() {
	return (kbd_ctrl_status() & KBD_STAT_OUTBUF);
}

//	spin until can_read
static inline void kbd_wait_read() {
	while (!kbd_can_read());
}

//	spin until can_write
static inline void kbd_wait_write() {
	while (!kbd_can_write());
}

//	read one byte from the keyboard
static inline u8 kbd_read() {
	kbd_wait_read();
	return kbd_enc_read();
}

//	send command to encoder
static inline void kbd_enc_cmd(u8 command) {
	kbd_wait_write();
	port_outb(KBD_ENC, command);
}

//	send command to controller
static inline void kbd_ctrl_cmd(u8 command) {
	kbd_wait_write();
	port_outb(KBD_CTRL, command);
}

//	empty output buffer
static inline void kbd_flush_outbuf() {
	while (kbd_can_read()) {
		kbd_enc_read();
	}
}

//	get configuration
static u8 kbd_ctrl_getconf(int flag) {
	kbd_ctrl_cmd(KBD_CTRL_GETCONF);
	u8 conf = kbd_read();
	return (conf & flag) ? TRUE : FALSE;
}

//	set given configuration flag
static void kbd_ctrl_setconf(int flag, int state) {
	kbd_ctrl_cmd(KBD_CTRL_GETCONF);
	u8 conf = kbd_read();

	if (state) {
		conf |= flag;
	} else {
		conf &= ~flag;
	}

	kbd_ctrl_cmd(KBD_CTRL_SETCONF);
	kbd_enc_cmd(conf);
}

//	control keyboard LEDs
void kbd_set_leds(int scroll, int num, int caps) {
	u8 command = 0;

	command |= scroll ? KBD_LEDS_SCROLL : 0;
	command |= num ? KBD_LEDS_NUM : 0;
	command |= caps ? KBD_LEDS_CAPS : 0;

	kbd_enc_cmd(KBD_ENC_SETLEDS);
	kbd_enc_cmd(command);
}

//	execute controller self-test
static int kbd_self_test() {
	kbd_ctrl_cmd(KBD_CTRL_SELFTEST);
	return (kbd_read() == KBD_CTRL_TESTOK) ? TRUE : FALSE;
}

//	handle keyboard	interrupt (IRQ 1, ISR 33)
static void kbd_handler(struct isr_regs regs) {
	u8 scancode = kbd_read();
	if (scancode == 0xE0) {
		kbd_state.escaped = TRUE;
	} else if (scancode == 0xF0) {
		kbd_state.isbreak = TRUE;
	} else {
		int keycode = scancode_set2[scancode + (kbd_state.escaped ? 128 : 0)];
		int state = kbd_state.isbreak ? KEY__UP : KEY__DOWN;

		kbd_state.val = 0;		// reset state

		if (keycode != KEY_NONE && kbd_callback) {
			struct kbd_event ev = {keycode, state};
			kbd_callback(ev);
		}
	}
}

//	initialize keyboard
void kbd_init() {
	kbd_ctrl_cmd(KBD_CTRL_KBDOFF);
	kbd_ctrl_cmd(KBD_CTRL_MOUSEOFF);
	kbd_flush_outbuf();

	kbd_ctrl_setconf(KBD_CONF_TRANSLATE, FALSE);
	kbd_ctrl_setconf(KBD_CONF_KBDINTS, FALSE);
	kbd_ctrl_setconf(KBD_CONF_MOUSEINTS, FALSE);
	kbd_flush_outbuf();

	if (!kbd_self_test()) {
		PANIC("Keyboard controller self-test failed\n");
	}

	kbd_ctrl_cmd(KBD_CTRL_TESTPORT1);
	if (kbd_read() != 0) {
		PANIC("Keyboard interface self-test failed\n");
	}
	kbd_flush_outbuf();

	kbd_enc_cmd(KBD_ENC_RESET);
	if (kbd_read() != KBD_RES_ACK) {
		PANIC("Keyboard reset failed\n");
	}

	kbd_set_leds(0, 0, 0);
	kbd_flush_outbuf();

	kbd_ctrl_setconf(KBD_CONF_KBDINTS, TRUE);
	kbd_ctrl_cmd(KBD_CTRL_KBDON);
	kbd_flush_outbuf();

	isr_set_handler(IRQ1, kbd_handler);
}

void kbd_set_callback(kbd_event_f func) {
	kbd_callback = func;
}
