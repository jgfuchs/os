#include <multiboot.h>
#include <printf.h>

void print_multiboot_info(u32 mbi_addr) {
    struct multiboot_info *mbi = (struct multiboot_info *)mbi_addr;
    u32 flags = mbi->flags;

    printf("Multiboot information:\n");
    printf("\tflags: 0x%x\n", flags);

    if (GET_BIT(flags, MBI_FLAGS_MEM)) {
        printf("\tmemory:\n");
        printf("\t\tlower: %u KB\n", mbi->mem_lower);
        printf("\t\tupper: %u KB\n", mbi->mem_upper);
    }

    if (GET_BIT(flags, MBI_FLAGS_DEV)) {
        printf("\tboot device:\n");
        printf("\t\tdrive: %x\n", mbi->drive);
        printf("\t\tpartition: %x,%x,%x\n", mbi->part1, mbi->part2, mbi->part3);
    }

    if (GET_BIT(flags, MBI_FLAGS_CMD)) {
        printf("\tcommand line: \"%s\"\n", (char *)mbi->cmdline);
    }

    if (GET_BIT(flags, MBI_FLAGS_MODS)) {
        printf("\tmodules: %d\n", mbi->mods_count);
    }

    // flags 4 and 5 are mutually exlusive
    if (GET_BIT(flags, MBI_FLAGS_AOUT)) {
        printf("\tsymbol table: AOUT\n");
    } else if (GET_BIT(flags, MBI_FLAGS_ELF)) {
        printf("\tsymbol table: ELF\n");
    }

    if (GET_BIT(flags, MBI_FLAGS_MMAP)) {
        printf("\tmemory map:\n");
        struct mbi_mmap *mmap = (struct mbi_mmap *)mbi->mmap_addr;
        while ((u32)mmap < mbi->mmap_addr + mbi->mmap_len) {
            printf("\t\t%s:", (mmap->type == MBI_MMAP_AVAIL) ? "FREE" : "resv");
            printf(", base: 0x%x", (u32)mmap->base);
            printf(", len: 0x%x (%u KB)\n", (u32)mmap->len,
                (u32)(mmap->len / 1024));

            mmap = (struct mbi_mmap *)((u32)mmap + mmap->size + sizeof(u32));
        }
    }

    if (GET_BIT(flags, MBI_FLAGS_DRIVE)) {
        printf("\tdrive info available\n");
    }

    if (GET_BIT(flags, MBI_FLAGS_CONF)) {
        printf("\tconfig table available\n");
    }

    if (GET_BIT(flags, MBI_FLAGS_NAME)) {
        printf("\tbootloader: %s\n", (char *)mbi->name);
    }

    if (GET_BIT(flags, MBI_FLAGS_APM)) {
        printf("\tAPM table available\n");
    }

    if (GET_BIT(flags, MBI_FLAGS_VBE)) {
        printf("\tVBE info available\n");
    }
}
