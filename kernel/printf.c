/*
	formatted output to vga console
*/

#include <con.h>
#include <printf.h>

//	convert int to string
static void itoa(char *buf, char mode, int val) {
	static char digits[] = "0123456789ABCDEF";

	char *p = buf;
	int base = 10;

	unsigned int x = val;

	//	minus sign?
	if (mode == 'd') {
		if (val < 0) {
			*p++ = '-';
			x = -val;

			buf++;
		}
	} else if (mode == 'x') {
		base = 16;
	} else if (mode == 'o') {
		base = 8;
	}

	//	the actual math
	do {
		int rem = x % base;
		*p++ = digits[rem];
	} while (x /= base);

	*p = 0;

	//	reverse string
	char *p1 = buf;
	char *p2 = p - 1;

	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;

		p1++;
		p2--;
	}
}

//	get int from void*
#define INT(x) *((int *) x)

//	get char from void*
#define CHAR(x) *((char *) x)

//	formatted printing
void printf(const char *format, ...) {
	char **args = (char **) &format;
	char buf[32];
	char c, *p;

	args++;

	while ((c = *format++) > 0) {
		if (c == '%') {
			c = *format++;
			switch (c) {
				case '%':
					con_putc('%');
					break;
				case 'c':
					con_putc(CHAR(args++));
					break;
				case 'd':
				case 'u':
				case 'x':
				case 'o':
					itoa(buf, c, INT(args++));
					con_puts(buf);
					break;
				case 'p':
					itoa(buf, 'x', (u32) *args++);
					con_puts(buf);
					break;
				case 's':
					p = *args++;
					if (p) {
						con_puts(p);
					} else {
						con_puts("(null)");
					}

					break;
				default:
					break;
			}
		} else {
			con_putc(c);
		}
	}
}
