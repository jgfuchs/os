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
// clang-format off
#define MBI_FLAGS_MEM   0
#define MBI_FLAGS_DEV   1
#define MBI_FLAGS_CMD   2
#define MBI_FLAGS_MODS  3
#define MBI_FLAGS_AOUT  4
#define MBI_FLAGS_ELF   5
#define MBI_FLAGS_MMAP  6
#define MBI_FLAGS_DRIVE 7
#define MBI_FLAGS_CONF  8
#define MBI_FLAGS_NAME  9
#define MBI_FLAGS_APM   10
#define MBI_FLAGS_VBE   11
// clang-format on

// multiboot data
struct multiboot_info {
    u32 flags;

    // if MBI_FLAGS_MEM
    u32 mem_lower;
    u32 mem_upper;

    // if MBI_FLAGS_DEV
    union {
        u32 boot_device;
        struct {
            u8 part3;
            u8 part2;
            u8 part1;
            u8 drive;
        };
    };

    // if MBI_FLAGS_CMD
    u32 cmdline;

    // if MBI_FLAGS_MODS
    u32 mods_count;
    u32 mods_addr;

    union {
        // if MBI_FLAGS_AOUT
        struct {
            u32 aout_tabsize;
            u32 aout_strsize;
            u32 aout_addr;
            u32 _aout_res;
        };

        // if MBI_FLAGS_ELF
        struct {
            u32 elf_num;
            u32 elf_size;
            u32 elf_addr;
            u32 elf_shndx;
        };
    };

    // if MBI_FLAGS_MMAP
    u32 mmap_len;
    u32 mmap_addr;

    // if MBI_FLAGS_DRIVE
    u32 drives_len;
    u32 drives_addr;

    // if MBI_FLAGS_CONF
    u32 conf_table;

    // if MBI_FLAGS_NAME
    u32 name;

    // if MBI_FLAGS_APM
    u32 apm_table;

    // if MBI_FLAGS_VBE
    u32 vbe_ctrl_info;
    u32 vbe_mode_info;
    u32 vbe_mode;
    u32 vbe_seg;
    u32 vbe_off;
    u32 vbe_len;
};

// pointed to by multiboot_info.mods_addr
struct mbi_module {
    u32 start;
    u32 end;
    u32 string;
    u32 _res;
};

// pointed to by multiboot_info.mmap_addr
struct mbi_mmap {
    u32 size;
    u64 base;
    u64 len;

#define MBI_MMAP_AVAIL 1
    u32 type;
};

// drive struct modes
#define MBI_DRIVE_CHS 0
#define MBI_DRIVE_LBA 1

// drive structure
struct mbi_drive {
    u32 size;
    u8 num;
    u8 mode;
    u16 cylinders;
    u8 heads;
    u8 sectors;

    // VLA with all IO ports
    u16 ports[];
};

void print_multiboot_info(u32 mbi_addr);

#endif  //_MULTIBOOT_H_
