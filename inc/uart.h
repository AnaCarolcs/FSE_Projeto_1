#ifndef UART_H

#define UART_H

#include <termios.h>

#define SOLIC 0x23
#define TEMP_INT 0xC1
#define TEMP_POTENC 0xC2
#define SOLIC_EST 0xC3

#define ENV_SINAL 0x16
#define ENV_SINAL_SUB 0xD1

void init_UART(const char *path);
void close_UART();

void send_control_signal_UART(int data);

int read_int_UART();
float read_float_UART();

#endif