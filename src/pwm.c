#include "pwm.h"
#include "stdio.h"
int init_pwm()
{
    int setup = wiringPiSetup(); /* initialize wiringPi setup */

    if (setup != 0)
        return -1;

    return 0;
}

void send_signal(int intensity)
{
    pinMode(VENTOINHA, OUTPUT);
    softPwmCreate(VENTOINHA, 0, 100);
    pinMode(RESISTOR, OUTPUT);
    softPwmCreate(RESISTOR, 0, 100);

    if (intensity >= 0)
    {

        softPwmWrite(VENTOINHA, 0);
        softPwmWrite(RESISTOR, intensity);
    }
    else
    {
        if (intensity <= -40)
            softPwmWrite(VENTOINHA, -intensity);
        else
            softPwmWrite(VENTOINHA, 0);

        softPwmWrite(RESISTOR, 0);
    }
}

void end_pwm()
{
    pinMode(VENTOINHA, OUTPUT);
    softPwmCreate(VENTOINHA, 0, 100);
    pinMode(RESISTOR, OUTPUT);
    softPwmCreate(RESISTOR, 0, 100);

    softPwmStop(VENTOINHA);
    softPwmStop(RESISTOR);
}