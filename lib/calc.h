/*
 * calc.h
 *
 *  Created on: 19.05.2019
 *      Author: fb
 */



#ifndef LIB_CALC_H_
#define LIB_CALC_H_

#include <stdint.h>

#define RAMP_LENGTH          32
#define MM_PER_REV            5.0f
#define STEPS_PER_REV       200.0f
#define MICROSTEPS_PER_STEP   4.0f

#define MICROSTEPS_PER_MM (MICROSTEPS_PER_STEP*STEPS_PER_REV/MM_PER_REV)
#define STEPS_PER_DISTANCE(x) ((uint32_t)(((float) x)*MICROSTEPS_PER_MM))

#endif /* LIB_CALC_H_ */
