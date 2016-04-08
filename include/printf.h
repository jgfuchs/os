/*
    formatted output to vga console
*/

#ifndef _PRINTF_H_
#define _PRINTF_H_

void printf(const char *format, ...) __attribute__((format(printf, 1, 2)));

#endif  //_PRINTF_H_
