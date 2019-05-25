#include "gptm.h"

int volatile * const TIMER1TAMATCHR = (int *) 0x40031028;

Void gptm_isr(UArg arg0)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
    *TIMER1TAMATCHR -= 200;
    if (*TIMER1TAMATCHR <= 0) {
        *TIMER1TAMATCHR = 0xFAAA;
    }
    GPIO_write(Board_LED0, Board_LED_OFF);
    GPIO_write(Board_LED1, Board_LED_OFF);
    //GPIOPinWrite(GPIO_PORTF_BASE, Board_LED2, 0);


    // Read the current state of the GPIO pin and
    // write back the opposite state
    /*
    if(GPIOPinRead(GPIO_PORTF_BASE, Board_LED2)) {
        GPIOPinWrite(GPIO_PORTF_BASE, Board_LED2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, Board_LED0, 0);
    }
    else {
        GPIOPinWrite(GPIO_PORTF_BASE, Board_LED2, 1);
        GPIOPinWrite(GPIO_PORTF_BASE, Board_LED0, 0);
    }
    */

}



void gptm_init(void)
{

    int volatile * const RCGCTIMER = (int *) 0x400FE604;
    *RCGCTIMER |= (1<<1);

    int volatile * const TIMER1CTL = (int *) 0x4003100C;
    *TIMER1CTL &= ~(1<<0);

    int volatile * const TIMER1CFG = (int *) 0x40031000;
    *TIMER1CFG = 0x00000004;

    int volatile * const TIMER1TAMR = (int *) 0x40031004;
    *TIMER1TAMR |= (2<<0) | (1<<3);
    *TIMER1TAMR &= ~(1<<2);

    *TIMER1CTL &= ~(1<<14);

    int volatile * const TIMER1TAILR = (int *) 0x40031028;
    *TIMER1TAILR = 0x0E;

    *TIMER1TAMATCHR = 0xFAAA;
    *TIMER1CTL |= (1<<0);


#if (0)
    uint32_t ui32Period;

    //SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    Hwi_Handle hwi;
    Error_Block eb;

    Error_init(&eb);

    /* Install interrupt handler */
    hwi = Hwi_create(INT_TIMER0B, &gptm_isr, NULL, &eb);
    if (hwi == NULL) {
        System_abort("Can't create GPTM Hwi");
    }


    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    ui32Period = (SysCtlClockGet() / 10) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_B, ui32Period -1);

    IntEnable(INT_TIMER0B);
    //TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
    //IntMasterEnable();
    Hwi_enableInterrupt(INT_TIMER0B);

    TimerEnable(TIMER0_BASE, TIMER_B);

#endif


}




