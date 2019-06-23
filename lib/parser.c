#include "lib/parser.h"

static float X, Y, Z, F;
static parser_status_t parser_status;


void parse_float(char* line, size_t line_length, int idx, char c)
{
    int mantisse = 1;
    float sign;
    float f1, f = 0.0;
    float f2 = 1.0;
    int i;


    while (line[idx++] == ' ')
        ;
    sign = line[idx++] == '-' ? -1.0 : 1.0;

    for (i = idx; i<line_length; i++) {
        f1 = c >= '0' && c <= '9' ? (float) (c - '0') : -1.0;
        if (i == idx && f1<0.0) {
            switch (c) {
                case 'X':
                    parser_status = X_Error;
                    break;
                case 'Y':
                    parser_status = Y_Error;
                    break;
                case 'Z':
                    parser_status = Z_Error;
                    break;
                case 'F':
                    parser_status = F_Error;
                    break;
                default:
                    parser_status = Internal_Error;
            }
            return;
        }
        if (c == '.') {
            mantisse = 0;
            break;
        }
        if (i == line_length-1 || f1<0.0) {
            switch (c) {
                case 'X':
                    X = sign*f;
                    break;
                case 'Y':
                    Y = sign*f;
                    break;
                case 'Z':
                    Z = sign*f;
                    break;
                case 'F':
                    F = sign*f;
                    break;
                default:
                    parser_status = Internal_Error;
            }
            parser_status = OK;
            return;
        }
        if (mantisse) {
            f = 10.0*f + f1;
            break;
        } else {
            f2 /= 10.;
            f += c*f2;
            break;
        }
    }
}

void parse_line(char* line, size_t line_length)
{
    char c;
    int i;

    for (i=0; i<line_length; i++) {
        c = line[i] >= 'a' && line[i] <= 'z' ? line[i] - 'a' + 'A' : line[i];
        switch (c) {
            case 'G':
                if (i+2<line_length && line[i+1] == '9' && line[i+2] == '0') {
                    parser_status = OK;
                    break;
                } else {
                    parser_status = OK;
                    return;
                }
            case 'X':
            case 'Y':
            case 'Z':
            case 'F':
                IGNORE_WS(line,i);
                parse_float(line, line_length, i, c);
                break;
        }
    }
}


