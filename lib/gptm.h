#ifndef LIB_GPTM_H_
#define LIB_GPTM_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#include <ti/sysbios/hal/Hwi.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include <ti/drivers/GPIO.h>
#include "Board.h"
#include <ti/drivers/GPIO.h>



void gptm_init(void);

//Void gptm_isr(UArg arg0);


#endif /* LIB_GPTM_H_ */
