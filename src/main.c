#include <stdio.h>

#include "temperature.h"
#include "terminal.h"

int main()
{
    temperature_info parameters;

    get_temperature_parameters(&parameters);

    printf("%.2f %d", parameters.interna, parameters.control_mode);

    function();

    get_temperature_parameters(&parameters);

    printf("%.2f %d", parameters.interna, parameters.control_mode);

    return 0;
}
