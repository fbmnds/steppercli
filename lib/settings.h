#ifndef LIB_SETTINGS_H_
#define LIB_SETTINGS_H_


#include <stdint.h>

#define RAMP_LENGTH          32
#define MM_PER_REV            5.0f
#define STEPS_PER_REV       200.0f
#define MICROSTEPS_PER_STEP   4.0f

#define MICROSTEPS_PER_MM (MICROSTEPS_PER_STEP*STEPS_PER_REV/MM_PER_REV)
#define MICROSTEPS_PER_DISTANCE(x) ((uint32_t)(((float) x)*MICROSTEPS_PER_MM))

#define CPU_CLOCK_MHz 40
#define PWM_WIDTH_uS  10
#define PWM_WIDTH_MHz 1000000/PWM_WIDTH_uS
#define PWM_LOAD_uS   100
#define PWM_WIDTH_CPU_CYCLES (PWM_WIDTH_uS*CPU_CLOCK_MHz)

#endif /* LIB_SETTINGS_H_ */
