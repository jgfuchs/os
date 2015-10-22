/*
	Global Descriptor Table setup
*/

#include <gdt.h>
#include <types.h>

//	assembly in dt_load.s
extern void gdt_load(u32);

//	access byte
#define GDT_PRES(x)	((x) << 7)
#define GDT_PRIV(x)	((x) << 5)
#define GDT_ONE		(1 << 4)
#define GDT_EXEC(x)	((x) << 3)
#define GDT_RDWR(x)	((x) << 1)

//	flags byte
#define GDT_GRAN(x)	((x) << 7)
#define GDT_SIZE(x) ((x) << 6)

//	kernel segments
#define GDT_CODE0	GDT_PRES(1) | GDT_PRIV(0) | GDT_ONE | GDT_EXEC(1) | GDT_RDWR(1)
#define GDT_DATA0	GDT_PRES(1) | GDT_PRIV(0) | GDT_ONE | GDT_EXEC(0) | GDT_RDWR(1)

//	user segments
#define GDT_CODE3	GDT_PRES(1) | GDT_PRIV(3) | GDT_ONE | GDT_EXEC(1) | GDT_RDWR(1)
#define GDT_DATA3	GDT_PRES(1) | GDT_PRIV(3) | GDT_ONE | GDT_EXEC(0) | GDT_RDWR(1)

//	all use the same value
#define GDT_FLAGS	(GDT_GRAN(1) | GDT_SIZE(1) | 0x0f)

//	one segment descriptor
struct gdt_entry {
	u16 limit;
	u16 base_l;
	u8 base_m;
	u8 access;
	u8 flags;	// also stores top 4 bits of limit
	u8 base_h;
} __attribute__ ((packed));

//	pointer to GDT
struct gdt_desc {
	u16 size;
	u32 base;
} __attribute__ ((packed));

//	the GDT itself
struct gdt_entry gdt[5];

//	pointer used with LGDT
struct gdt_desc gdtr;

//	create one segment descriptor
static void gdt_create(int ind, u32 base, u32 limit, u8 access, u8 flags) {
	struct gdt_entry *g = &gdt[ind];

	g->limit = limit & 0xFFFF;
	g->flags = (limit >> 16) & 0x0F;
	g->flags |= flags & 0xF0;

	g->base_l = base & 0xFFFF;
	g->base_m = (base >> 16) & 0xFF;
	g->base_h = (base >> 24) & 0xFF;

	g->access = access;
}

void gdt_init() {
	gdt_create(0, 0, 0, 0, 0);
	gdt_create(1, 0, 0xFFFFF, GDT_CODE0, GDT_FLAGS);
	gdt_create(2, 0, 0xFFFFF, GDT_DATA0, GDT_FLAGS);
	gdt_create(3, 0, 0xFFFFF, GDT_CODE3, GDT_FLAGS);
	gdt_create(4, 0, 0xFFFFF, GDT_DATA3, GDT_FLAGS);

	gdtr.size = sizeof(struct gdt_entry) * 5 - 1;
	gdtr.base = (u32) &gdt;

	gdt_load((u32) &gdtr);
}
