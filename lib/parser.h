#ifndef LIB_PARSER_H_
#define LIB_PARSER_H_

#include <stddef.h>
#include <stdbool.h>


typedef enum {
    G90 = 0,
    Undefined_Gcode
} g_code_cmd_t;

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

typedef struct {
    float X;
    float Y;
    float Z;
    float F;
} g_xyzf_t;

typedef struct {
    g_xyzf_t* g_xyzf;
    parser_status_t parser_status;
    g_code_cmd_t g_code;
} parsed_g_code_t;


void parse_reset(parsed_g_code_t* pgc);
void parse_line(char* line, size_t line_length, parsed_g_code_t* pgc);


//#define IGNORE_WS(s,i) (while ((s)[(i)++] == ' '))
//#define TO_UPPER(c)    do { c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c; } until (1);
//#define CTOI (c)       do { c >= '0' && c <= '9' ? (float) (c - '0') : -1.0; } until (1);

#endif /* LIB_PARSER_H_ */
