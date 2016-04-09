/*
    first C code executed
*/

#include <con.h>
#include <gdt.h>
#include <idt.h>
#include <int.h>
#include <kbd.h>
#include <multiboot.h>
#include <panic.h>
#include <pic.h>
#include <printf.h>
#include <term.h>
#include <timer.h>
#include <types.h>

void kmain(u32 magic, u32 mbi_addr) {
    if (magic != MULTIBOOT_MAGIC)
        return;

    int_off();

    con_init();
    printf("\nVGA output initialized\n");

    print_multiboot_info(mbi_addr);

    // gdt_init();
    // printf("Created GDT\n");
    //
    // idt_init();
    // printf("Created IDT\n");
    //
    // timer_init();
    // printf("Started timer at %u hz\n", HZ);
    //
    // kbd_init();
    // printf("Initialized keyboard\n");

    while (1)
        ;
}
