#include <stdio.h>

#include "uart.h"

int main()
{
    init_UART("/dev/serial0");

    printf("%.2f\n", read_float_UART(TEMP_INT));
    printf("%.2f\n", read_float_UART(TEMP_POTENC));
    printf("%d\n", read_int_UART());

    close_UART();

    return 0;
}
