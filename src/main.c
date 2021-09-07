#include <stdio.h>

#include "control.h"

#include "bme280.h"
#include "log.h"
#include "pwm.h"

int main()
{
    bme280Init(1, 0x76);
    create_csv();
    init_pwm();

    control();

    end_pwm();

    return 0;
}
