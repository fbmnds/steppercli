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






Void pwmFxn(UArg arg0, UArg arg1)
{
    PWM_Handle pwm1;
    PWM_Handle pwm2 = NULL;
    PWM_Params params;
    uint16_t   pwmPeriod = 3000;      // Period and duty in microseconds
    //uint16_t   duty = 0;
    //uint16_t   dutyInc = 100;
    uint16_t   pwmDuty = 0;
    //uint16_t   dutyInc = 100;


    PWM_Params_init(&params);
    params.period = pwmPeriod;
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

    /* Loop forever incrementing the PWM duty */
    while (1) {
        //mask = ;// + event1; //"evtPWMPrint" + "evtPWMSetDuty";
        if (Event_pend(evtPWM, Event_Id_00, Event_Id_NONE, BIOS_WAIT_FOREVER)) {
            unsigned int t = PWM_getPeriodMicroSecs(pwm1);
            printf("PWM period (us): %d\n", t);
            printf("PWM duty: %u\n", pwmDuty);
            fflush(stdout);
        }
    }
}


void pwm_start(void)
{
    //PWM_setDuty(pwm1, (pwmPeriod >> 1));
}

void pwm_stop(void)
{
    //PWM_setDuty(pwm1, 0);
}

void pwm_setDuty(uint16_t duty)
{
    //pwmDuty = duty;
    //PWM_setDuty(pwm1, duty);
}

void pwm_print(void)
{
    /*
    unsigned int t = PWM_getPeriodMicroSecs(pwm1);
    printf("PWM period (us): %d\n", t);
    printf("PWM duty: %u\n", pwmDuty);
    fflush(stdout);
    */
}
