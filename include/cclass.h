/*
    character classes
*/

#include <string.h>
#include <types.h>

static inline int is_digit(char c) {
    return (c >= '0') && (c <= '9');
}

static inline int is_xdigit(char c) {
    return is_digit(c) || ((c >= 'A') && (c <= 'F'));
}

static inline int is_upper(char c) {
    return (c >= 'A') && (c <= 'Z');
}

static inline int is_lower(char c) {
    return (c >= 'a') && (c <= 'z');
}

static inline int is_alpha(char c) {
    return is_upper(c) || is_lower(c);
}

static inline int is_alnum(char c) {
    return is_alpha(c) || is_digit(c);
}

static inline int is_punct(char c) {
    static const char *puncts = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    return strchr(puncts, c) != NULL;
}

static inline int is_space(char c) {
    static const char *spaces = "\t\n\f\r\v ";
    return strchr(spaces, c) != NULL;
}

static inline int is_print(char c) {
    return is_alnum(c) || is_punct(c) || is_space(c);
}
