#ifndef LIB_CONSOLE_H_
#define LIB_CONSOLE_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/knl/Task.h>

#include "lib/settings.h"
#include "lib/pwm.h"

extern Event_Handle evtPWM;
extern uint16_t pwmDuty;

Void consoleFxn(UArg arg0, UArg arg1);

#endif /* LIB_CONSOLE_H_ */
