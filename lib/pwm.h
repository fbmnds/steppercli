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
#include "gptm.h"

extern Event_Handle evtPWM;
static uint16_t pwmDuty = 0;

extern int volatile * const RCGCTIMER;

extern int volatile * const TIMER1CTL;
extern int volatile * const TIMER1CFG;
extern int volatile * const TIMER1TAILR;
extern int volatile * const TIMER1TAMATCHR;
extern int volatile * const TIMER1TAMR;

extern int volatile * const RCGCGPIO;
extern int volatile * const GPIOFDEN;
extern int volatile * const GPIOFDIR;
extern int volatile * const GPIOAFSEL;
extern int volatile * const GPIOPCTL;



Void pwmFxn(UArg arg0, UArg arg1);

#define EVT_PWMPRINT   Event_Id_00
#define EVT_PWMSETDUTY Event_Id_01
#define EVT_PWMSTART   Event_Id_02
#define EVT_PWMSTOP    Event_Id_03


#endif /* LIB_PWM_H_ */
