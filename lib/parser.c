#include "parser.h"



typedef struct {
    bool ok;
    float f;
    int pos;
} maybe_float_t;
static maybe_float_t _mf;
static maybe_float_t* mf = &_mf;

//float X, Y, Z, F;
//parser_status_t parser_status;
//g_code_cmd_t g_code;

void parse_float(char* line, size_t line_length, int idx)
{
    int mantisse = 1;
    float sign = 1;
    float f1, f = 0.0;
    float f2 = 1.0;

    int i;

    mf->ok = false;
    mf->f = -1.0;
    mf->pos = idx;

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
            continue;
        }
        if (f1<0.0) {
            mf->ok = true;
            mf->f = sign*f;
            mf->pos = i;
            return;
        }
        if (mantisse) {
            f = 10.0*f + f1;
            continue;
        } else {
            f2 /= 10.;
            f += f1*f2;
            continue;
        }
    }
    if (i == line_length || line[i] != '\0') {
        mf->ok = true;
        mf->f = sign*f;
        mf->pos = i;
        return;
    } else {
        /* never */
        mf->ok = false;
        mf->pos = idx;
        return;
    }
}

void parse_line(char* line, size_t line_length, parsed_g_code_t* pgc)
{
    char c;
    int i, idx;


    i = 0;

    while (line[i] == ' ')
        i++;
    idx = i;

    if (i == line_length) {
        pgc->parser_status = OK;
        return;
    }

    if (i < line_length && line[i] == '(') {
        pgc->parser_status = OK;
        return;
    }

    for (; i<line_length && line[i] != '\0'; i++) {
        c = line[i] >= 'a' && line[i] <= 'z' ? line[i] - 'a' + 'A' : line[i];
        if (c == 'G') {
            if (i == idx && i+2<line_length && line[i+1] == '9' && line[i+2] == '0') {
                i +=2;
                pgc->g_code = G90;
                continue;
            } else {
                pgc->parser_status = G_Error;
                return;
            }
        } else if (c == 'X' || c == 'Y' || c == 'Z' || c == 'F') {
            i++;
            parse_float(line, line_length, i);
            i = mf->pos-1;
            switch (c) {
            case 'X':
                if (!mf->ok) {
                    pgc->parser_status = X_Error;
                    return;
                }
                pgc->g_xyzf->X = mf->f;
                break;
            case 'Y':
                if (!mf->ok) {
                    pgc->parser_status = Y_Error;
                    return;
                }
                pgc->g_xyzf->Y = mf->f;
                break;
            case 'Z':
                if (!mf->ok) {
                    pgc->parser_status = Z_Error;
                    return;
                }
                pgc->g_xyzf->Z = mf->f;
                break;
            case 'F':
                if (!mf->ok) {
                    pgc->parser_status = F_Error;
                    return;
                }
                pgc->g_xyzf->F = mf->f;
                break;
            default:
                /* never */
                break;
            }
            continue;
        }
    }
    pgc->parser_status = OK;
}


void parse_reset(parsed_g_code_t* pgc)
{
    pgc->parser_status = Undefined_Parser_Status;
    pgc->g_code = Undefined_Gcode;
    if (pgc->g_xyzf) {
        pgc->g_xyzf->X = 0.0;
        pgc->g_xyzf->Y = 0.0;
        pgc->g_xyzf->Z = 0.0;
        pgc->g_xyzf->F = 0.0;
    } else {
        // TODO: assertion
    }
}

