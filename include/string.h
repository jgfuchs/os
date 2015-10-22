/*
	generic string/memory functions, like libc's string.h
*/

#ifndef _STRING_H_
#define _STRING_H_

#include <types.h>

//	set block of memory
static inline void memset(void *d, int c, u32 n) {
	u8 *p = d;
	while (n--)
		*p++ = c;
}

//	zero a block of memory
static inline void memclr(void *d, u32 n) {
	memset(d, 0, n);
}

//	copy block of memory
static inline void memcpy(void *d, const void *s, u32 n) {
	u8 *dp = d;
	const u8 *sp = s;
	while (n--)
		*dp++ = *sp++;
}

//	compare two blocks of memory
static inline int memcmp(const void *d, const void *s, u32 n) {
	const u8 *dp = d;
	const u8 *sp = s;

	while (n--) {
		if (*dp != *sp)
			return *dp - *sp;

		dp++;
		sp++;
	}

	return 0;
}

//	find byte in memory
static inline void *memchr(void *d, u8 c, u32 n) {
	u8 *dp = d;
	while (n-- && (*dp++ != c));
	return n ? dp : NULL;
}

//	string copy
static inline void strcpy(char *d, const char *s) {
	while ((*d++ = *s++));
}

//	string copy up to limit
static inline void strncpy(char *d, const char *s, u32 n) {
	while (n-- && (*d++ = *s++));
}

//	string length
static inline int strlen(const char *str) {
	int len;
	for (len = 0; *str; str++, len++);
	return len;
}

//	string concatenate
static inline void strcat(char *d, const char *s) {
	d = d + strlen(d);
	while ((*d++ = *s++));
}

//	string concatenate up to limit
static inline void strncat(char *d, const char *s, u32 n) {
	d = d + strlen(d);
	while (n-- && (*d++ = *s++));
}

//	string compare
static inline int strcmp(const char *d, const char *s) {
	while ((*d && *s) && (*d == *s)) {
		d++;
		s++;
	}

	return *d - *s;
}

//	string compare up to limit
static inline int strncmp(const char *d, const char *s, u32 n) {
	while (n--) {
		if (*d != *s)
			return *d - *s;

		d++;
		s++;
	}

	return 0;
}

//	find char in string
static inline const char *strchr(const char *d, char c) {
	while (*d && (*d++ != c));
	return *d ? d : NULL;
}

#endif //_STRING_H_

