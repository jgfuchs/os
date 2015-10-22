/*
	main interrupt handling code (called by isr_stubs.s)
*/

#include <isr.h>
#include <pic.h>

//	all handler funcs
isr_f isr_handlers[256];

//	set a callback function
void isr_set_handler(u8 intn, isr_f func) {
	isr_handlers[intn] = func;
}

//	handles all interrupts
void isr_handle(struct isr_regs regs) {
	isr_f handler = isr_handlers[regs.intn];
	if (handler) {
		handler(regs);
	}

	if (IS_IRQ(regs.intn)) {
		pic_eoi(regs.intn - IRQ0);
	}
}
