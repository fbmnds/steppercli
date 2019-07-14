#ifndef LIB_STEPPER_H_
#define LIB_STEPPER_H_

#include <stdint.h>
#include <stdio.h>

#include "settings.h"
#include "parser.h"

typedef enum {
    axisX,
    axisY,
    axisZ,
#ifdef XA_AXIS
    axisXA,
#endif
#ifdef XA_AXIS
    axisYA,
#endif
#ifdef XA_AXIS
    axisZA,
#endif
} axis_t;

typedef enum {
    Forward = 1,
    Backward = 0
} direction_t;

typedef struct {
    axis_t      axis;
    direction_t dir;
    uint32_t    steps;
    uint16_t    freq;
} st_block_t;



void print_damped_interval(float lower_bound, float upper_bound);
void reset_stb(st_block_t* stb, uint16_t stb_len);
void g_xyzf_to_stb(g_xyzf_t* g_xyzf, st_block_t* stb, uint16_t stb_len);

#endif /* LIB_STEPPER_H_ */
