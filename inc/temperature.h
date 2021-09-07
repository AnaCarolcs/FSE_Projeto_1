#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#define CONTROL_USER 1
#define TEMPERATURE_USER 2
#define HISTERESE_USER 3
#define PID_PARAMETES_USER 4

#include "temperature.h"
#include "bme280.h"
#include "uart.h"

struct temperature_info
{
    float interna;
    float externa;
    int histerese;
    int referencia;
    int kp, ki, kd;
    int control_mode;
} typedef temperature_info;

struct data_parameters
{
    int dt1;
    int dt2;
    int dt3;
    float temp;
} typedef data_parameters;

void set_user_mode(int option, data_parameters data);

void get_temperature_parameters(temperature_info *output);

#endif