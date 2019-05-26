#include "gptm.h"

int volatile * const RCGCTIMER = (int *) 0x400FE604;

int volatile * const TIMER1CTL = (int *) 0x4003100C;
int volatile * const TIMER1CFG = (int *) 0x40031000;
int volatile * const TIMER1TAILR = (int *) 0x40031028;
int volatile * const TIMER1TAMATCHR = (int *) 0x40031030;
int volatile * const TIMER1TAMR = (int *) 0x40031004;

int volatile * const RCGCGPIO = (int *) 0x400FE608;
int volatile * const GPIOFDEN = (int *) 0x4002551C;     //0x4002551C; // APB - AHB: 0x4002D51C
int volatile * const GPIOFDIR = (int *) 0x40025400;     //0x40025400; // APB - AHB: 0x4002D400
int volatile * const GPIOAFSEL = (int *) 0x40025420;    //0x40025420; // APB - AHB: 0x4002D420
int volatile * const GPIOPCTL = (int *) 0x4002552C;     //0x4002552C; // APB - AHB: 0x4002D52C


#if(0)
Void gptm_isr(UArg arg0)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);


    *TIMER1TAMATCHR -= 200;
    if (*TIMER1TAMATCHR <= 0) {
        *TIMER1TAMATCHR = 0xFAAA;
    }

    //GPIO_write(Board_LED0, Board_LED_OFF);
    //GPIO_write(Board_LED1, Board_LED_OFF);
    //GPIOPinWrite(GPIO_PORTF_BASE, Board_LED2, 0);


    // Read the current state of the GPIO pin and
    // write back the opposite state

    if(GPIO_read(Board_LED2)) {
        GPIO_write(Board_LED2, 0);
        //GPIO_write(Board_LED0, 1);
    }
    else {
        GPIO_write(Board_LED2, 1);
        //GPIO_write(Board_LED0, 0);
    }
}
#endif


void gptm_init(void)
{
    // enable the clock for the Timer1 module.
    *RCGCTIMER |= (1<<1);

    /*
     * TM4C123GH6PM-DataSheet_spms376e.pdf
     * 11.4.5 PWM Mode
     * A timer is configured to PWM mode using the following sequence:
     *
     * 1. Ensure the timer is disabled (the TnEN bit is cleared) before making any changes.
     */
    *TIMER1CTL &= ~(1<<0);

    /*
     * 2. Write the GPTM Configuration (GPTMCFG) register with a value of 0x0000.0004.
     */
    *TIMER1CFG = 0x00000004;

    /*
     * 3. In the GPTM Timer Mode (GPTMTnMR) register, set the TnAMS bit to 0x1,
     *    the TnCMR bit to 0x0, and the TnMR field to 0x2.
     */
    *TIMER1TAMR |= (1<<3);
    *TIMER1TAMR &= ~(1<<2);
    *TIMER1TAMR |= (2<<0);

    /*
     * 4. Configure the output state of the PWM signal (whether or not it is inverted)
     *    in the TnPWML field of the GPTM Control (GPTMCTL) register.
     */
    *TIMER1CTL &= ~(1<<6);

    /*
     * 5. If a prescaler is to be used, write the prescale value
     *    to the GPTM Timer n Prescale Register (GPTMTnPR).
     */

    /*
     * 6. If PWM interrupts are used, configure the interrupt condition
     *    in the TnEVENT field in the GPTMCTL register and enable the interrupts
     *    by setting the TnPWMIE bit in the GPTMTnMR register.
     *    Note that edge detect interrupt behavior is reversed when the PWM output is inverted
     *    (see page 737).
     */
    *TIMER1TAMR |= (1<<9);

    /*
     * 7. Load the timer start value into the GPTM Timer n Interval Load (GPTMTnILR) register.
     */
    *TIMER1TAILR = 0xFEEE;


    /*
     * 8. Load the GPTM Timer n Match (GPTMTnMATCHR) register with the match value.
     */
    *TIMER1TAMATCHR = 0xFE00;


    /* 9. Set the TnEN bit in the GPTM Control (GPTMCTL) register to enable the timer
     * and begin generation of the output PWM signal.
     */
    *TIMER1CTL |= (1<<0);


    *RCGCGPIO |= (1<<5);
    *GPIOFDEN |= (1<<2);
    *GPIOFDIR |= (1<<2);
    *GPIOAFSEL |= (1<<2);
    *GPIOPCTL |= (7<<8);
}




