cmake_minimum_required (VERSION 2.8)
PROJECT (kernel)

INCLUDE_DIRECTORIES (include)

SET (CMAKE_C_FLAGS "-m32 -g -ffreestanding -fno-exceptions -nostdlib -nostdinc -fno-stack-protector -Wall")
SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

ENABLE_LANGUAGE (ASM_NASM)

FILE (GLOB_RECURSE C_SOURCES "kernel/*.c")
FILE (GLOB_RECURSE ASM_SOURCES "kernel/*.asm")

ADD_LIBRARY (kernel.img STATIC ${C_SOURCES} ${ASM_SOURCES})
ADD_CUSTOM_COMMAND (TARGET kernel.img POST_BUILD COMMAND
ld -m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/link.ld -o kernel.img ${CMAKE_BINARY_DIR}/libkernel.img.a -Map mapfile)
