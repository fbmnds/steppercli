#ifndef LIB_CONSOLE_H_
#define LIB_CONSOLE_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include <xdc/runtime/System.h>

#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>

#include "settings.h"
#include "pwm.h"
#include "parser.h"
#include "stepper.h"


extern volatile uint32_t PWM_period;
extern volatile uint32_t PWM_duty;

//extern float X, Y, Z, F;
//extern parser_status_t parser_status;
//extern g_code_t g_code;

Void consoleFxn(UArg arg0, UArg arg1);

#endif /* LIB_CONSOLE_H_ */
