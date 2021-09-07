#ifndef __BME280__
#define __BME280__

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int bme280Init(int iChannel, int iAddr);
int bme280ReadValues(int *T, int *P, int *H);

#endif // __BME280__