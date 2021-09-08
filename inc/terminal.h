#ifndef TERMINAL_H
#define TERMINAL_H

#include "temperature.h"
#include "control.h"

void clear_terminal();

void set_header();
void set_menu_options();
void *read_user_option();

int show_change_mode_control();
int show_change_temperature();
int show_change_histerese();
void show_change_pid_parameters(data_parameters *user_params);

extern void quit();

#endif