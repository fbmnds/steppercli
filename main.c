/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
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
 *    ======== uartconsole.c ========
 */

#include <file.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <UARTUtils.h>
#include <USBCDCD_LoggerIdle.h>

/* Example/Board Header files */
#include "Board.h"

/* Application Header files */
#include "lib/console.h"
#include "lib/settings.h"
#include "lib/pwm.h"
#include "lib/gptm.h"


#define CONSOLESTACKSIZE     1536

Task_Struct taskCStruct;
Char taskCStack[CONSOLESTACKSIZE];

#define PWMSTACKSIZE     1536

Task_Struct taskPWMStruct;
Char taskPWMStack[PWMSTACKSIZE];


/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions. */
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();
    Board_initUSB(Board_USBDEVICE);
    Board_initPWM();

    /* Construct BIOS objects */
    Task_Params taskCParams;

    Task_Params_init(&taskCParams);
    taskCParams.stackSize = CONSOLESTACKSIZE;
    taskCParams.stack = &taskCStack;
    Task_construct(&taskCStruct, (Task_FuncPtr)consoleFxn, &taskCParams, NULL);

    Task_Params taskPWMParams;

    Task_Params_init(&taskPWMParams);
    taskPWMParams.stackSize = PWMSTACKSIZE;
    taskPWMParams.stack = &taskPWMStack;
    Task_construct(&taskPWMStruct, (Task_FuncPtr)pwmFxn, &taskPWMParams, NULL);

    gptm_init();

    /* Turn on user LED */
    GPIO_write(Board_LED2, Board_LED_ON);

    /*
     *  Add the UART device to the system.
     *  All UART peripherals must be setup and the module must be initialized
     *  before opening.  This is done by Board_initUART().  The functions used
     *  are implemented in UARTUtils.c.
     */
    add_device("UART", _MSA, UARTUtils_deviceopen,
               UARTUtils_deviceclose, UARTUtils_deviceread,
               UARTUtils_devicewrite, UARTUtils_devicelseek,
               UARTUtils_deviceunlink, UARTUtils_devicerename);

    /* Open UART0 for writing to stdout and set buffer */
    freopen("UART:0", "w", stdout);
    setvbuf(stdout, NULL, _IOLBF, 128);

    /* Open UART0 for reading from stdin and set buffer */
    freopen("UART:0", "r", stdin);
    setvbuf(stdin, NULL, _IOLBF, 128);

    /*
     *  Initialize UART port 0 used by SysCallback.  This and other SysCallback
     *  UART functions are implemented in UARTUtils.c. Calls to System_printf
     *  will go to UART0, the same as printf.
     */
    UARTUtils_systemInit(0);

    System_printf("Starting the UART Console example\n");

    /* Initialize the USB CDC device for logging transport */
    USBCDCD_init();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
