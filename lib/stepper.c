#include "stepper.h"


void print_damped_interval(float lower_bound, float upper_bound)
{
    int i;

    for(i=0; i<DAMP_COEFF_LEN; i++)
        printf("%5.2f\n", (lower_bound + (upper_bound-lower_bound)*damp_coeff[i]));
}

void reset_stb(st_block_t* stb, uint16_t stb_len)
{
    int i;

    //TODO: assertion stb
    for(i=0; i<stb_len; i++) stb[i].steps = 0;
}

void g_xyzf_to_stb(g_xyzf_t* g_xyzf, st_block_t* stb, uint16_t stb_len)
{
    int i;
    direction_t dirX = g_xyzf->X < 0.0 ? Backward : Forward;
    float absX = dirX == Forward ? g_xyzf->X : -1.0*g_xyzf->X;
    float capF = (uint16_t)(MICROSTEPS_PER_DISTANCE(g_xyzf->F < F_MIN ?
            F_MIN : (g_xyzf->F > F_MAX ? F_MAX : g_xyzf->F))/60);
    //TODO: assertion g_xyzf, stb
    //TODO: implement Y, Z
    //TODO: implement (g_xyzf->X < MIN_DAMP_DIST)

    if (g_xyzf->X < MIN_DIST) return;
    if (g_xyzf->X < MIN_DAMP_DIST) return;

    /* g_xyzf->X >= MIN_DAMP_DIST */

    for(i=0; i<DAMP_COEFF_LEN; i++) {
        stb[i].axis  = axisX;
        stb[i].dir   = dirX;
        stb[i].steps = 1;
        stb[i].freq = F_MIN_FREQ + (capF - F_MIN_FREQ)*damp_coeff[i];
    }
    stb[DAMP_COEFF_LEN].steps = MICROSTEPS_PER_DISTANCE(absX) - (2*DAMP_COEFF_LEN);
    stb[DAMP_COEFF_LEN].steps = stb[DAMP_COEFF_LEN].steps > 0 ? stb[DAMP_COEFF_LEN].steps : 0;
    stb[DAMP_COEFF_LEN].freq  = capF;
    for(i=DAMP_COEFF_LEN+1; i<(2*DAMP_COEFF_LEN+1); i++) {
        stb[i].axis  = axisX;
        stb[i].dir   = dirX;
        stb[i].steps = 1;
        stb[i].freq  = F_MIN_FREQ + (capF - F_MIN_FREQ)*damp_coeff[2*DAMP_COEFF_LEN-i];
    }
}
