/*
    operations on individual bits
    Feb 2013, Julian Fuchs
*/

#include <types.h>

#ifndef _BITOPS_H_
#define _BITOPS_H_

#define BIT(n) (1 << (n))

#define SET_BIT(word, n) (word | BIT(n))
#define GET_BIT(word, n) (word & BIT(n))
#define CLEAR_BIT(word, n) (word & ~BIT(n))

#endif  //_BITOPS_H_
