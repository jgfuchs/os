/*
    multiboot information struct
*/

#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

#include <bitops.h>
#include <types.h>

// multiboot magic number
#define MULTIBOOT_MAGIC 0x2BADB002

// whether various fields are valid
#define MBD_FLAGS_MEM (0)
#define MBD_FLAGS_DEV (1)
#define MBD_FLAGS_CMD (2)
#define MBD_FLAGS_MODS (3)
#define MBD_FLAGS_SYMS (4)
#define MBD_FLAGS_MMAP (6)
#define MBD_FLAGS_DRIVE (7)
#define MBD_FLAGS_CONF (8)
#define MBD_FLAGS_NAME (9)
#define MBD_FLAGS_APM (10)
#define MBD_FLAGS_VBE (11)

// multiboot data
struct mbd {
    u32 flags;

    // if MBD_FLAGS_MEM
    u32 mem_lower;
    u32 mem_upper;

    // if MBD_FLAGS_DEV
    union {
        u32 boot_device;
        struct {
            u8 drive;
            u8 part1;
            u8 part2;
            u8 part3;
        };
    };

    // if MBD_FLAGS_CMD
    u32 cmdline;

    // if MBD_FLAGS_MODS
    u32 mods_count;
    u32 mods_addr;

    // if MBD_FLAGS_SYMS
    u32 elf_num;
    u32 elf_size;
    u32 elf_addr;
    u32 elf_shndx;

    // if MBD_FLAGS_MMAP
    u32 mmap_len;
    u32 mmap_addr;

    // if MBD_FLAGS_DRIVE
    u32 drives_len;
    u32 drives_addr;

    // if MBD_FLAGS_CONF
    u32 conf_tab;

    // if MBD_FLAGS_NAME
    u32 name;

    // if MBD_FLAGS_APM
    u32 apm_tab;

    // if MBD_FLAGS_VBE
    u32 vbe_ctrl_info;
    u32 vbe_mode_info;
    u32 vbe_mode;
    u32 vbe_seg;
    u32 vbe_off;
    u32 vbe_len;
};

// type field, any other value = reserved
#define MBD_MMAP_AVAIL 1

// memory map
struct mbd_mmap {
    u32 size;
    u64 base;
    u64 len;
    u32 type;
};

// drive struct modes
#define MBD_DRIVE_CHS 0
#define MBD_DRIVE_LBA 1

// drive structure
struct mbd_drive {
    u32 size;
    u8 num;
    u8 mode;
    u16 cylinders;
    u8 heads;
    u8 sectors;

    // VLA with all IO ports
    u16 ports[];
};

#endif  //_MULTIBOOT_H_
