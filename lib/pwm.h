#ifndef LIB_PWM_H_
#define LIB_PWM_H_

#include <stdint.h>
#include <stdbool.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>

#include <ti/drivers/GPIO.h>

#include <driverlib/sysctl.h>
#include <driverlib/pwm.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>

#define PART_TM4C123GH6PM 1
#include <driverlib/pin_map.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"

#include "../tm4c/Board.h"



#define F_MIN_CT     37500
#define F_MAX_CT      5000
#define MICROSTEP_CT   100

static volatile uint32_t PWM_period = F_MAX_CT;
static volatile uint32_t PWM_duty   = 2500;
static volatile uint32_t pwmCount;

void pwm_isr(void);
void pwm_init(void);
void pwm_start(void);
void pwm_stop(void);
void pwm_update(void);
void pwm_setPeriod(uint32_t pwmPeriod);
void pwm_setDuty(uint32_t pwmDuty);


#endif /* LIB_PWM_H_ */
