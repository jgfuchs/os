/*
	timer functions, Programmable Interval Timer (PIT) interface
*/

#ifndef _TIMER_H_
#define _TIMER_H_

#include <types.h>

//	ticks per second
#define HZ 40

//	set up PIT
void timer_init();

//	get current tick
u32 timer_ticks();

//	sleep for # of milliseconds
void timer_sleep(int ms);

#endif //_TIMER_H_
