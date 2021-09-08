#ifndef CONTROL_H
#define CONTROL_H

#define ON_OFF_MODE 0
#define PID_MODE 1

#include "control_lcd_16x2.h"
#include "temperature.h"
#include "terminal.h"
#include "pid.h"
#include "pwm.h"
#include "log.h"

void *control();

int get_pid_control(temperature_info params);
int get_on_off_control(temperature_info params);

temperature_info get_temperature_params();

#endif