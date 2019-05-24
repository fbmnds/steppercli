/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== pwm.c ========
 */


#include "pwm.h"

void pwm_print(PWM_Handle pwm1);

uint16_t pwmDuty = 0;

Void pwmFxn(UArg arg0, UArg arg1)
{
    PWM_Handle pwm1;
    PWM_Handle pwm2 = NULL;
    PWM_Params params;
    uint16_t   pwmPeriod = 3000;      // Period and duty in microseconds
    //uint16_t   duty = 0;
    //uint16_t   dutyInc = 100;

    //uint16_t   dutyInc = 100;
    UInt events;


    PWM_Params_init(&params);
    params.period = pwmPeriod;  // ~ microstep_delay(current_feed_rate, sin x²-ramp)
    pwm1 = PWM_open(Board_PWM0, &params);
    if (pwm1 == NULL) {
        System_abort("Board_PWM0 did not open");
    }

    if (Board_PWM1 != Board_PWM0) {
        params.polarity = PWM_POL_ACTIVE_LOW;
        pwm2 = PWM_open(Board_PWM1, &params);
        if (pwm2 == NULL) {
            System_abort("Board_PWM1 did not open");
        }
    }

    /*
     * PWM_setDuty(pwm1, duty);  // fix ~ microstep
     */

    /*
     * register isrPWMCtl: PWMGenIntRegister
     * PWMGenIntTrigDisable
     * init isrPWMCounter -> 0
     */


    /* Loop forever incrementing the PWM duty */
    while (1) {
        int mask = EVT_PWMPRINT + EVT_PWMSETDUTY;
        events = Event_pend(evtPWM, mask, Event_Id_NONE, BIOS_WAIT_FOREVER);
        if (events & EVT_PWMPRINT) {
            pwm_print(pwm1);
        } else if (events & EVT_PWMSETDUTY) {
            PWM_setDuty(pwm1, pwmDuty);
        }
    }
}

void pwm_print(PWM_Handle pwm1)
{
    unsigned int t = PWM_getPeriodMicroSecs(pwm1);
    printf("PWM period (us): %d\n", t);
    printf("PWM duty: %u\n", pwmDuty);
    fflush(stdout);
}

void pwm_start(/*#microsteps*/)
{
    /*
     * PWMGenIntClear
     * set isrPWMCounter -> #microsteps
     * PWMGenIntTrigEnable
     * PWMGenEnable
     */
}

//void pwm_stop(void)
//{

    /*
     * isrPWMCtl:
     * TODO: add fault handler -> based on ADC input from encoder
     *      PWMGenIntClear
     *      lookup sin(x²)[isrPWMCounter] -> PWMGenPeriodSet
     *      decrement isrPWMCounter
     *      if isrPWMCounter == 0 -> PWMGenDisable; PWMGenIntTrigDisable
     */
//}

void pwm_setDuty(uint16_t duty)
{
    //pwmDuty = duty;
    //PWM_setDuty(pwm1, duty);
}


