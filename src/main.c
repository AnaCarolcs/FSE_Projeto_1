#include <pthread.h>
#include <stdio.h>

#include "control.h"
#include "terminal.h"

#include "control_lcd_16x2.h"
#include "bme280.h"
#include "log.h"
#include "pwm.h"

pthread_t CONTROL_THREAD, TERMINAL_THREAD;

void start()
{
    bme280Init(1, 0x76);
    create_csv();
    init_pwm();
    lcd_init();

    pthread_create(&CONTROL_THREAD, NULL, control, NULL);
    pthread_create(&TERMINAL_THREAD, NULL, read_user_option, NULL);
    pthread_join(CONTROL_THREAD, NULL);
    pthread_join(TERMINAL_THREAD, NULL);
}

void quit()
{
    end_pwm();
    ClrLcd();

    pthread_cancel(TERMINAL_THREAD);
    pthread_cancel(CONTROL_THREAD);
}

int main()
{

    start();

    return 0;
}
