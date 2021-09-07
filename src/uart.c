#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "uart.h"
#include "crc16.h"

unsigned char package[256];
unsigned short crc;

//190063441
char my_id[] = {3, 4, 4, 1};
char path[] = "/dev/serial0";

void create_default_package(int code, int sub_code)
{
    package[0] = 0x01;
    package[1] = code;
    package[2] = sub_code;
    memcpy(&package[3], my_id, 4);
}

void write_uart(int uart_device, const void *buffer, size_t bytes)
{
    int count;

    count = write(uart_device, buffer, bytes);

    if (count < 0)
    {
        perror("Can't write on UART");
        exit(0);
    }

    return;
}

void read_uart(int uart_device, void *buffer, size_t bytes)
{
    int count;

    count = read(uart_device, buffer, bytes);

    if (count < 0)
    {
        perror("Can't write on UART");
        exit(0);
    }

    return;
}

int init_UART(const char *path)
{
    struct termios defs;

    defs.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    defs.c_iflag = IGNPAR;
    defs.c_oflag = 0;
    defs.c_lflag = 0;

    int uart_device = open(path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart_device == -1)
    {
        perror("Can't open UART");
        exit(0);
    }

    tcflush(uart_device, TCIFLUSH);
    tcsetattr(uart_device, TCSANOW, &defs);

    return uart_device;
}

void close_UART(int uart_device)
{
    close(uart_device);
}

void send_control_signal_UART(int data)
{
    int uart_device = init_UART(path);

    create_default_package(ENV_SINAL, ENV_SINAL_SUB);

    memcpy((void *)(&package[3]), (void *)data, sizeof(int));

    crc = calcula_CRC(package, 4);

    memcpy((void *)(&package[4]), (void *)&crc, 1);

    crc = calcula_CRC(package, 5);

    memcpy((void *)(&package[5]), (void *)&crc, 1);

    write_uart(uart_device, (void *)&package, 6);

    sleep(1);

    close_UART(uart_device);
}

int read_int_UART()
{
    char tmp_char;
    int result;

    int uart_device = init_UART(path);

    create_default_package(SOLIC, SOLIC_EST);

    crc = calcula_CRC(package, 7);

    memcpy((void *)(&package[7]), (void *)&crc, 2);

    write_uart(uart_device, (void *)package, 9);

    sleep(1);

    read_uart(uart_device, (void *)&tmp_char, sizeof(char));

    read_uart(uart_device, (void *)&tmp_char, sizeof(char));

    read_uart(uart_device, (void *)&tmp_char, sizeof(char));

    read_uart(uart_device, &result, 4);

    read_uart(uart_device, (void *)&tmp_char, 2);

    close_UART(uart_device);

    return result;
}

float read_float_UART(int sub_code)
{
    char tmp_char;
    float result;

    int uart_device = init_UART(path);

    create_default_package(SOLIC, sub_code);

    crc = calcula_CRC(package, 7);

    memcpy((void *)(&package[7]), (void *)&crc, 2);

    write_uart(uart_device, (void *)&package, 9);

    sleep(1);

    read_uart(uart_device, (void *)&tmp_char, sizeof(char));

    read_uart(uart_device, (void *)&tmp_char, sizeof(char));

    read_uart(uart_device, (void *)&tmp_char, sizeof(char));

    read_uart(uart_device, (void *)&result, 4);

    read_uart(uart_device, (void *)&tmp_char, 2);

    close_UART(uart_device);

    return result;
}
