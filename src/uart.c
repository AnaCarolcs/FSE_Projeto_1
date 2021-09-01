#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "uart.h"
#include "crc16.h"

unsigned char package[256];
unsigned short crc;

void create_default_package(int code, int sub_code){
    package[0] = device_address;
    package[1] = code;
    package[2] = sub_code;
}

void write_uart(const void *buffer, size_t bytes)
{
    int count;

    count = write(uart_device, buffer, bytes);

    if (count < 0){
        perror("Can't write on UART");
        exit(0);
    }

    return;
}

void read_uart(void *buffer, size_t bytes)
{
    int count;

    count = read(uart_device, buffer, bytes);

    if (count < 0){
        perror("Can't write on UART");
        exit(0);
    }

    return;
}

void init_UART(const char *path)
{
    struct termios defs;

    defs.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    defs.c_iflag = IGNPAR;
    defs.c_oflag = 0;
    defs.c_lflag = 0;

    uart_device = open(path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart_device == -1){
        perror("Can't open UART");
        exit(0);
    }

    tcflush(uart_device, TCIFLUSH);
    tcsetattr(uart_device, TCSANOW, &defs);
}

void close_UART()
{
    close(uart_device);
}

void send_control_signal_UART(int data){
    create_default_package(ENV_SINAL, ENV_SINAL_SUB);

    memcpy((void *)(&package[3]), data, sizeof(int));

    crc = calcula_CRC(package, 4);

    memcpy((void *)(&package[4]), (void *)&crc, 1);

    crc = calcula_CRC(package, 5);

    memcpy((void *)(&package[5]), (void *)&crc, 1);

    write_uart((void *)package, 6);

    sleep(1);
}

int read_int_UART(){
    char tmp_char;
    int result;

    create_default_package(SOLIC, SOLIC_EST);

    crc = calcula_CRC(package, 3);

    memcpy((void *)(&package[3]), (void *)&crc, 1);

    crc = calcula_CRC(package, 4);

    memcpy((void *)(&package[4]), (void *)&crc, 1);

    write_uart((void *)package, 5);

    sleep(1);

    read_uart((void *)&tmp_char, sizeof(char));

    read_uart((void *)&tmp_char, sizeof(char));

    read_uart((void *)&tmp_char, sizeof(char));

    read_uart(&result, 4);

    read_uart((void *)&tmp_char, 1);
    read_uart((void *)&tmp_char, 1);

    return result;
}

float read_float_UART(int sub_code){
    char tmp_char;
    float result;

    create_default_package(SOLIC, sub_code);

    crc = calcula_CRC(package, 3);

    memcpy((void *)(&package[3]), (void *)&crc, 1);

    crc = calcula_CRC(package, 4);

    memcpy((void *)(&package[4]), (void *)&crc, 1);

    write_uart((void *)package, 5);

    sleep(1);

    read_uart((void *)&tmp_char, sizeof(char));

    read_uart((void *)&tmp_char, sizeof(char));

    read_uart((void *)&tmp_char, sizeof(char));

    read_uart(&result, 4);

    read_uart((void *)&tmp_char, 1);
    read_uart((void *)&tmp_char, 1);

    return result;
}
