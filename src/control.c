#include "control.h"

int last_on_off = 0;

int get_pid_control(temperature_info params)
{
    pid_configura_constantes(params.kp, params.ki, params.kd);
    pid_atualiza_referencia(params.referencia);

    int control_signal = pid_controle(params.interna);

    return control_signal;
}

int get_on_off_control(temperature_info params)
{
    int control_signal;

    float lower_bound = params.referencia - params.histerese / 2.0;
    float upper_bound = params.referencia + params.histerese / 2.0;

    if (params.interna >= upper_bound)
        control_signal = -100;
    else if (params.interna <= lower_bound)
        control_signal = 100;
    else
        control_signal = last_on_off;

    last_on_off = control_signal;

    return control_signal;
}

void control()
{
    while (1)
    {
        temperature_info temperature_params;
        int control_signal;

        get_temperature_parameters(&temperature_params);

        if (temperature_params.control_mode == ON_OFF_MODE)
            control_signal = get_on_off_control(temperature_params);
        else if (temperature_params.control_mode == PID_MODE)
        {
            control_signal = get_pid_control(temperature_params);
            last_on_off = 0;
        }

        send_signal(control_signal);
        send_control_signal_UART(control_signal);

        write_on_log(temperature_params, control_signal);

        sleep(10);

        break;
    }
}