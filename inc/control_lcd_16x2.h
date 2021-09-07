#ifndef PID_H_
#define PID_H_

#define I2C_ADDR 0x27

#define LCD_CHR 1
#define LCD_CMD 0

#define LINE1 0x80
#define LINE2 0xC0

#define LCD_BACKLIGHT 0x08
#define ENABLE 0b00000100

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

int fd;

void lcd_init();

void typeFloat(float myFloat);

void typeInt(int i);

void typeChar(char val);

void typeln(const char *s);

void lcdLoc(int line);

void lcd_byte(int bits, int mode);

void lcd_toggle_enable(int bits);

void ClrLcd(void);

#endif