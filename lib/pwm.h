#ifndef LIB_PWM_H_
#define LIB_PWM_H_

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>

/* Example/Board Header files */
#include "Board.h"

#include <stdio.h>

/* BIOS Header files */
#include <ti/sysbios/knl/Event.h>

/*
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
*/

extern Event_Handle evtPWM;

Void pwmFxn(UArg arg0, UArg arg1);

void pwm_start(void);
void pwm_stop(void);
//void pwm_setPeriod(uint16_t period);
void pwm_setDuty(uint16_t duty);
void pwm_print(void);

#endif /* LIB_PWM_H_ */
