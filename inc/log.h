#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "temperature.h"

void create_csv();
const char *get_time_info();
void write_on_log(temperature_info temp, int atuador);

#endif