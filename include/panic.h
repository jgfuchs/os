/*
	fail fatally
*/

#ifndef _PANIC_H_
#define _PANIC_H_

#include <printf.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__)

#define ASSERT(x, msg) if (!(x)) { PANIC(msg); }

static inline void panic(char *msg, char *file, int line) {
	printf("\nPANIC at %s:%d: %s\n", file, line, msg);

	asm volatile ("cli\nhlt\n");

	while (1);
}

#endif //_PANIC_H_
