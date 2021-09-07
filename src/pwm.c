#include "pwm.h"

int init_pwm(int pin)
{
    if (pin != RESISTOR && pin != VENTOINHA)
        return -1;

    int setup = wiringPiSetup(); /* initialize wiringPi setup */

    pinMode(pin, OUTPUT); /* set GPIO as output */

    int create = softPwmCreate(pin, 1, 100); /* set PWM channel along with range*/

    if (setup != 0 || create == -1)
        return -1;

    return 0;
}

void send_signal(int pin, int intensity)
{
    if (intensity >= 0)
    {
        if (pin == RESISTOR)
        {
            softPwmWrite(VENTOINHA, 0);
            softPwmWrite(pin, intensity);
        }
        else
        {
            if (intensity >= 40)
                softPwmWrite(pin, intensity);
            else
                softPwmWrite(pin, 0);

            softPwmWrite(RESISTOR, 0);
        }
    }
    else
    {
        softPwmWrite(VENTOINHA, 0);
        softPwmWrite(RESISTOR, 0);
    }
}

void end_pwm()
{
    softPwmWrite(VENTOINHA, 0);
    softPwmWrite(RESISTOR, 0);
}