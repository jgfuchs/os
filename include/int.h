/*
	interrupt management
*/

#ifndef _INT_H_
#define _INT_H_

//	enable all interrupts
static inline void int_on() {
	asm volatile ("sti");
}

//	disable all interrupts
static inline void int_off() {
	asm volatile ("cli");
}

//	emit interrupt
#define int_fire(x) asm volatile ("int $" #x)

#endif //_INT_H_
