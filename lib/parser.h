#ifndef LIB_PARSER_H_
#define LIB_PARSER_H_

#include <stddef.h>

typedef enum {
    G90 = 0
} g_code_t;

typedef enum {
    OK = 1,
    G_Error,
    X_Error,
    Y_Error,
    Z_Error,
    F_Error,
    Internal_Error
} parser_status_t;

//#define IGNORE_WS(s,i) (while ((s)[(i)++] == ' '))
//#define TO_UPPER(c)    do { c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c; } until (1);
//#define CTOI (c)       do { c >= '0' && c <= '9' ? (float) (c - '0') : -1.0; } until (1);

#endif /* LIB_PARSER_H_ */
