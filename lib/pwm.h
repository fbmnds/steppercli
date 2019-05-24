#ifndef LIB_PWM_H_
#define LIB_PWM_H_

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>

/* Example/Board Header files */
#include "Board.h"

#include <stdio.h>


extern Event_Handle evtPWM;

Void pwmFxn(UArg arg0, UArg arg1);

#define EVT_PWMPRINT   Event_Id_00
#define EVT_PWMSETDUTY Event_Id_01

#endif /* LIB_PWM_H_ */
