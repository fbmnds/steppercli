#include "lib/pwm.h"
// TivaWare(tm) Peripheral Driver Library USER’S GUIDE - SPMU298d, section 21

#define USE_SWI 0

void pwm_swi(void)
{
#if Use_SWI
    pwmCount++;
    GPIO_toggle(Board_LED2_RED);
#endif
}

void pwm_isr(void)
{
    PWMGenIntClear(PWM1_BASE, PWM_GEN_0, PWM_INT_CNT_ZERO);
#if Use_SWI
    Swi_post(PWMswi);
#else
    pwmCount++;
    GPIO_toggle(Board_LED2_RED);
#endif
}


void pwm_init(void)
{
    //SysCtlClockSet( SYSCTL_SYSDIV_2_5 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ );
    SysCtlPWMClockSet( SYSCTL_PWMDIV_64 );

#if 1
    // Enable the GPIO peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //
    // Wait for the GPIO module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        ;
#endif

    GPIOPinTypePWM( GPIO_PORTD_BASE, GPIO_PIN_0 );
    GPIOPinConfigure( GPIO_PD0_M1PWM0 );

    // Enable the PWM1 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    //
    // Wait for the PWM1 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))
        ;
    //
    // Configure the PWM generator for count down mode with immediate updates
    // to the parameters.
    //
    PWMGenConfigure(PWM1_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    //
    // Set the period.
    //
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, F_MAX_CT);
    //
    // Set the pulse width of PWM1 for a single microstep.
    //
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 2500);
    //
    // Start the timers in generator 0.
    //
    PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_0);

    PWMGenIntTrigEnable (PWM1_BASE, PWM_GEN_0, PWM_INT_CNT_ZERO) ;
    PWMIntEnable (PWM1_BASE, PWM_INT_GEN_0) ;

    IntEnable(INT_PWM1_0);
    IntMasterEnable();

}


inline void pwm_start(void)
{
    // Enable the outputs.
    //
    PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
}


inline void pwm_stop(void)
{
    // Disable the outputs.
    //
    PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, false);
}


void pwm_update(void)
{
    //PWMGenDisable(PWM1_BASE, PWM_GEN_0);
    // Set the period.
    //
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, PWM_period);
    //
    // Set the pulse width of PWM1.
    //
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, PWM_duty);
    //PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}


void pwm_setPeriod(uint32_t pwmPeriod)
{
    // Set the period.
    //
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, pwmPeriod);
}


void pwm_setDuty(uint32_t pwmDuty)
{
    // Set the pulse width of PWM1.
    //
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, pwmDuty);
}
