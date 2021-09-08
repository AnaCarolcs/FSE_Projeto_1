#include "temperature.h"

volatile int user_mode_control = 0;
volatile int user_mode_tmp = 0;
volatile int user_mode_hst = 0;
volatile int user_mode_pid = 0;

volatile int user_temperature;
volatile int user_histerese;
volatile int user_control;
volatile int user_kp;
volatile int user_ki;
volatile int user_kd;

void set_user_mode(int option, data_parameters data)
{
    switch (option)
    {
    case CONTROL_USER:
        if (data.dt1 != 0 && data.dt1 != 1)
        {
            user_mode_control = 0;
            break;
        }

        user_mode_control = 1;
        user_control = data.dt1;
        break;
    case TEMPERATURE_USER:
        if (data.dt1 <= 0)
        {
            user_mode_tmp = 0;
            break;
        }

        user_mode_tmp = 1;
        user_temperature = data.dt1;
        break;
    case HISTERESE_USER:
        if (data.dt1 <= 0)
        {
            user_mode_hst = 0;
            break;
        }

        user_mode_hst = 1;
        user_histerese = data.dt1;
        break;
    case PID_PARAMETES_USER:
        if (data.dt1 < 0)
        {
            user_mode_pid = 0;
            break;
        }

        user_mode_pid = 1;
        user_kp = data.dt1;
        user_ki = data.dt2;
        user_kd = data.dt3;
        break;

    default:
        break;
    }
}

void get_temperature_parameters(temperature_info *output)
{
    float potentiometer_tmp = read_float_UART(TEMP_POTENC);
    float internal_tmp = read_float_UART(TEMP_INT);
    int key_state = read_int_UART();

    int T, P, H;
    bme280ReadValues(&T, &P, &H);
    float external_tmp = (T - 150) / 100;

    if (user_mode_tmp == 1)
        output->referencia = user_temperature;
    else
        output->referencia = potentiometer_tmp;

    if (user_mode_control == 1)
        output->control_mode = user_control;
    else
        output->control_mode = key_state;

    if (user_mode_hst == 1)
        output->histerese = user_histerese;
    else
        output->histerese = 3;

    if (user_mode_pid == 1)
    {
        output->kp = user_kd;
        output->ki = user_ki;
        output->kd = user_kd;
    }
    else
    {
        output->kp = 5;
        output->ki = 1;
        output->kd = 5;
    }

    output->interna = internal_tmp;
    output->externa = external_tmp;
}