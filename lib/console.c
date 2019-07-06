#include "lib/console.h"


static unsigned int count;
static float distance;
//static uint32_t adjust;
static unsigned int sleepDur;
#define INPUT_LEN 128
static char input[INPUT_LEN];
static unsigned int cpuLoad;

void print_greeting(void)
{
    count = 1;
    printf("\f======== Welcome to the Console ========\n");
    printf("Enter a command followed by return.\n"
           "Type help for a list of commands.\n\n");

    printf("%d %% ", count++);
    fflush(stdout);
}

void print_valid_cmds(void)
{
    printf("Valid commands:\n"
    "- load: Get the CPU and task load.\n"
    "- calc: Calculate microsteps per distance [mm].\n"
    "- gcode: Parse G-code.\n"
    "- pwm_start: Start PWM.\n"
    "- pwm_stop: Stop PWM.\n"
    "- pwm_duty: Adjust PWM load.\n"
    "- pwm_print: Print PWM parameters.\n"
    "- sleep: Put the console task to sleep.\n"
    "- exit: Exit the console task.\n");
}

void do_sleep(void)
{
    /* Put the task to sleep for X ms. */
    printf("Enter a duration (ms): ");
    fflush(stdout);
    scanf("%d", &sleepDur);
    fflush(stdin);
    Task_sleep(sleepDur);
}

void do_exit(void)
{
    /* Exit the console task */
    printf("Are you sure you want to exit the console? Y/N: ");
    fflush(stdout);
    scanf("%s", input);
    fflush(stdin);
    if ((input[0] == 'y' || input[0] == 'Y') && input[1] == 0x00) {
        printf("Exiting console, goodbye.\n");
        //Task_exit();
    }
}

void do_calc(void)
{
    /* Calculate steps per distance */
    printf("Enter a distance (mm): ");
    fflush(stdout);
    scanf("%f", &distance);
    fflush(stdin);
    printf("Microsteps per distance: %" PRIu32 "\n", MICROSTEPS_PER_DISTANCE(distance));
    fflush(stdout);
}

void do_gcode(void)
{
    int i;

    fflush(stdin);
    for (i=0; i<INPUT_LEN;i++) input[i] = '\0';
    /* Request G-code */
    printf("Enter a G-code command: ");
    fflush(stdout);
    scanf("%s", input);
    fflush(stdin);
    parse_reset();
    parse_line(input, INPUT_LEN);
    if (parser_status == OK)
        printf("OK\n");
    else
        printf("Error code %d\n", parser_status);
    if (g_code == G90) printf("G90 ");
    printf("X %f Y %f Z %f F %f", X, Y, Z, F);
    fflush(stdout);
}

void do_pwm_duty (void)
{
    /* Adjust the PWM duty. */
    printf("Enter duty (us): ");
    fflush(stdout);
    scanf("%" PRIu32, &PWM_duty);
    fflush(stdin);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, PWM_period);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, PWM_duty);
}

/*
 *  ======== consoleFxn ========
 *  Task for this function is created statically. See the project's .cfg file.
 */
Void consoleFxn(UArg arg0, UArg arg1)
{
    /* printf goes to the UART com port */
    print_greeting();

    /* Loop forever receiving commands */
    while(true) {
        /* Get the user's input */
        scanf("%s", input);
        /* Flush the remaining characters from stdin since they are not used. */
        fflush(stdin);

        if (!strcmp(input, "load")) {
            /* Print the CPU load */
            cpuLoad = Load_getCPULoad();
            printf("CPU Load: %d\n", cpuLoad);
        }
        else if (!strcmp(input, "calc")) {
            do_calc();
        }
        else if (!strcmp(input, "gcode")) {
            do_gcode();
        }
        else if (!strcmp(input, "pwm_print")) {
            /* Print PWM parameter*/
            printf("PWM period (us): %d\n", PWM_period);
            printf("PWM duty: %u\n", PWM_duty);
            fflush(stdout);
        }
        else if (!strcmp(input, "pwm_start")) {
            /* Start PWM */
            pwm_start();
        }
        else if (!strcmp(input, "pwm_stop")) {
            /* Stop PWM */
            pwm_stop();
        }
        else if (!strcmp(input, "pwm_duty")) {
            do_pwm_duty();
        }
        else if (!strcmp(input, "sleep")) {
            do_sleep();
        }
        else if (!strcmp(input, "exit")) {
            do_exit();
        }
        else {
            print_valid_cmds();
        }

        printf("%d %% ", count++);
        fflush(stdout);
    }
}
