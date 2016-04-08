/*
    main interrupt handling code (called by isr_stubs.s)
*/

#ifndef _ISR_H_
#define _ISR_H_

#include <types.h>

// everything that is pushed before calling isr_handle
// arranged here in reverse order that they were pushed
struct isr_regs {
    u32 ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecs, eax;
    u32 intn, err;
    u32 eip, cs, eflags, useresp, ss;
};

// callback function typedef
typedef void (*isr_f)(struct isr_regs);

// set a callback function
void isr_set_handler(u8 intn, isr_f func);

#endif  //_ISR_H_
