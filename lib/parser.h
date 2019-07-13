#ifndef LIB_PARSER_H_
#define LIB_PARSER_H_

#include <stddef.h>
#include <stdbool.h>


typedef enum {
    G90 = 0,
    Undefined_Gcode
} g_code_t;

typedef enum {
    OK = 1,
    G_Error,
    X_Error,
    Y_Error,
    Z_Error,
    F_Error,
    Internal_Error,
    Undefined_Parser_Status
} parser_status_t;

extern float X, Y, Z, F;
extern parser_status_t parser_status;
extern g_code_t g_code;

void parse_reset(void);
void parse_line(char* line, size_t line_length);


//#define IGNORE_WS(s,i) (while ((s)[(i)++] == ' '))
//#define TO_UPPER(c)    do { c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c; } until (1);
//#define CTOI (c)       do { c >= '0' && c <= '9' ? (float) (c - '0') : -1.0; } until (1);

#endif /* LIB_PARSER_H_ */
