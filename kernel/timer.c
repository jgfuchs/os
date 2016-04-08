/*
    timer functions, Programmable Interval Timer (PIT) interface
*/

#include <isr.h>
#include <pic.h>
#include <portio.h>
#include <timer.h>

#include <printf.h>

#define PIT_CMD 0x43  // command port
#define PIT_CH0 0x40  // data port for channel 0

#define PIT_SET 0x34  // command to set frequency

#define PIC_BASE_FREQ 1193182  // freq before division

static volatile u32 ticks = 0;

static void timer_handler(struct isr_regs regs) {
    ticks++;
}

// set up PIT and IRQs
void timer_init() {
    u32 div = PIC_BASE_FREQ / HZ;

    u8 divl = div & 0xFF;
    u8 divh = (div >> 8) & 0xFF;

    port_outb(PIT_CMD, PIT_SET);
    port_outb(PIT_CH0, divl);
    port_outb(PIT_CH0, divh);

    isr_set_handler(IRQ_00, timer_handler);
}

// get current tick
u32 timer_ticks() {
    return ticks;
}

// sleep for # of milliseconds
void timer_sleep(int ms) {
    // the resolution in ms of each tick
    u32 tick_ms = 1000 / HZ;

    // the # of ticks that this sleep requires
    u32 sleep_ticks = ms / tick_ms;

    // the tick value at which this sleep is over
    u32 target_ticks = ticks + sleep_ticks;

    // spin
    while (ticks < target_ticks)
        ;
}
