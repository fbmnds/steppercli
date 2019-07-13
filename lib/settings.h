#ifndef LIB_SETTINGS_H_
#define LIB_SETTINGS_H_


#include <stdint.h>

#define MM_PER_REV            5.0f
#define STEPS_PER_REV       200.0f
#define MICROSTEPS_PER_STEP   4.0f

#define MICROSTEPS_PER_MM (MICROSTEPS_PER_STEP*STEPS_PER_REV/MM_PER_REV)
#define MICROSTEPS_PER_DISTANCE(x) ((uint32_t)(((float) x)*MICROSTEPS_PER_MM))

#define PWM_CLOCK_MHz 20
#define PWM_WIDTH_uS  10
#define PWM_WIDTH_MHz (1000000/PWM_WIDTH_uS)
#define PWM_LOAD_uS   100
#define PWM_WIDTH_CPU_CYCLES (PWM_WIDTH_uS*CPU_CLOCK_MHz)

#define DAMP_COEFF_LEN 32
static float damp_coeff[DAMP_COEFF_LEN] = {
    0.0014,
    0.0056,
    0.0126,
    0.0224,
    0.0350,
    0.0503,
    0.0685,
    0.0894,
    0.1131,
    0.1394,
    0.1684,
    0.2001,
    0.2342,
    0.2707,
    0.3095,
    0.3505,
    0.3933,
    0.4378,
    0.4838,
    0.5308,
    0.5785,
    0.6265,
    0.6742,
    0.7213,
    0.7670,
    0.8108,
    0.8519,
    0.8897,
    0.9232,
    0.9517,
    0.9744,
    0.9904
};


#endif /* LIB_SETTINGS_H_ */
