#include "lib/parser.h"


typedef struct {
    bool ok;
    float f;
    int pos;
} maybe_float_t;


void parse_float(char* line, size_t line_length, int idx, maybe_float_t* mf)
{
    int mantisse = 1;
    float sign;
    float f1, f = 0.0;
    float f2 = 1.0;

    int i;


    while (line[idx] == ' ')
        idx++;

    if (line[idx] == '-') {
        sign = -1.0;
        idx++;
    }

    for (i = idx; i<line_length; i++) {
        f1 = line[i] >= '0' && line[i] <= '9' ? (float) (line[i] - '0') : -1.0;
        if (i == idx && f1<0.0) {
            mf->ok = false;
            mf->pos = idx;
            return;
        }
        if (line[i] == '.') {
            mantisse = 0;
            break;
        }
        if (f1<0.0) {
            mf->ok = true;
            mf->f = sign*f;
            mf->pos = i;
            return;
        }
        if (mantisse) {
            f = 10.0*f + f1;
            break;
        } else {
            f2 /= 10.;
            f += f1*f2;
            break;
        }
    }
    if (i == line_length) {
        mf->ok = true;
        mf->f = sign*f;
        mf->pos = line_length;
        return;
    } else {
        /* never */
        mf->ok = false;
        mf->pos = idx;
        return;
    }
}

void parse_line(char* line, size_t line_length)
{
    char c;
    int i, idx;
    maybe_float_t* mf;

    i = 0;

    while (line[i] == ' ')
        i++;
    idx = i;

    if (i == line_length) {
        parser_status = OK;
        return;
    }

    if (i < line_length && line[i] == '(') {
        parser_status = OK;
        return;
    }

    for (; i<line_length; i++) {
        c = line[i] >= 'a' && line[i] <= 'z' ? line[i] - 'a' + 'A' : line[i];
        if (c == 'G') {
            if (i == idx && i+2<line_length && line[i+1] == '9' && line[i+2] == '0') {
                i +=3;
                break;
            } else {
                parser_status = G_Error;
                return;
            }
        } else if (c == 'X' || c == 'Y' || c == 'Z' || c == 'F') {
            i++;
            parse_float(line, line_length, i, mf);
            i = mf->pos;
           switch (c) {
            case 'X':
                if (mf->ok) {
                    X = mf->f;
                } else {
                    parser_status = X_Error;
                }
                break;
            case 'Y':
                if (mf->ok) {
                    Y = mf->f;
                } else {
                    parser_status = Y_Error;
                }
                break;
            case 'Z':
                if (mf->ok) {
                    Z = mf->f;
                } else {
                    parser_status = Z_Error;
                }
                break;
            case 'F':
                if (mf->ok) {
                    F = mf->f;
                } else {
                    parser_status = F_Error;
                }
                break;
            default:
                /* never */
                break;
            }
            break;
        }
    }
    parser_status = OK;
}


