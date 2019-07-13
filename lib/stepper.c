#include "stepper.h"

void print_damped_interval(float lower_bound, float upper_bound)
{
    int i;

    for(i=0; i<DAMP_COEFF_LEN; i++) printf("%5.2f\n", (lower_bound + (upper_bound-lower_bound)*damp_coeff[i]));
}

