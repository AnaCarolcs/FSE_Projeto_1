#ifndef PWM_H
#define PWM_H

#include <wiringPi.h> /* include wiringPi library */
#include <softPwm.h>  /* include header file for software PWM */

#define RESISTOR 4
#define VENTOINHA 5

int init_pwm(int pin);
void send_signal(int pin, int intensity);
void end_pwm();

#endif