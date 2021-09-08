#include "terminal.h"

int show_menu_options = 1;

void clear_terminal()
{
    system("clear");
    fflush(stdout);
}

void set_header()
{
    temperature_info temp_params = get_temperature_params();

    printf("███████████████████");
    printf(" Controlador de Temperatura - V1.0 ");
    printf("███████████████████\n\n");
    printf("                                                         By: Ana Carolina\n\n\n");

    printf("Estado atual do sistema\n\n");
    printf("Temperatura interna: %02.2f\n", temp_params.interna);
    printf("Temperatura de referência: %02d\n", temp_params.referencia);
    printf("Temperatura externa: %02.2f\n", temp_params.externa);
    printf("Modo de controle: %s\n\n\n", temp_params.control_mode == 0 ? "ON/OFF" : "PID");
};

void set_menu_options()
{
    if (show_menu_options == 0)
        return;

    clear_terminal();
    set_header();

    printf("O que deseja fazer?\n\n");
    printf("(1) - Modificar modo de controle\n");
    printf("(2) - Modificar temperatura\n");
    printf("(3) - Modificar histerese (PID)\n");
    printf("(4) - Modificar parâmetros (PID)\n\n");
    printf("(5) - Encerrar o sistema\n\n\n");
}

int show_change_mode_control()
{
    int input;

    clear_terminal();
    set_header();

    printf("Digite a opção desejada\n\n");
    printf("(0) - ON/OFF\n");
    printf("(1) - PID\n");
    printf("(2) - Definir pela chave\n\n");

    scanf("%d", &input);

    if (input < 0 && input >= 2)
        printf("\n\n Valor inválido! Mudança não computada\n");

    return input;
}

int show_change_temperature()
{
    int input;

    clear_terminal();
    set_header();

    printf("Digite a nova temperatura de referência\n\n");

    scanf("%d", &input);

    if (input < 0 && input >= 100)
        printf("\n\n Valor inválido! Mudança não computada\n");

    return input;
}

int show_change_histerese()
{
    int input;

    clear_terminal();
    set_header();

    printf("Digite a nova histerese\n\n");

    scanf("%d", &input);

    if (input < 0 && input >= 100)
        printf("\n\n Valor inválido! Mudança não computada\n");

    return input;
}

void show_change_pid_parameters(data_parameters *user_params)
{
    int kp, ki, kd;

    clear_terminal();
    set_header();

    printf("Digite o novo KP\n\n");
    scanf("%d", &kp);
    printf("Digite o novo KI\n\n");
    scanf("%d", &ki);
    printf("Digite o novo KD\n\n");
    scanf("%d", &kd);

    user_params->dt1 = kp;
    user_params->dt2 = ki;
    user_params->dt3 = kd;
}

void *read_user_option()
{
    data_parameters user_params;
    char option;

    do
    {
        option = getchar();

        switch (option)
        {
        case '1':
            show_menu_options = 0;
            user_params.dt1 = show_change_mode_control();
            set_user_mode(1, user_params);
            show_menu_options = 1;
            break;
        case '2':
            show_menu_options = 0;
            user_params.dt1 = show_change_temperature();
            set_user_mode(2, user_params);
            show_menu_options = 1;
            break;
        case '3':
            show_menu_options = 0;
            user_params.dt1 = show_change_histerese();
            set_user_mode(3, user_params);
            show_menu_options = 1;
            break;
        case '4':
            show_menu_options = 0;
            show_change_pid_parameters(&user_params);
            set_user_mode(4, user_params);
            show_menu_options = 1;
            break;
        default:
            break;
        }

    } while (option != '5');

    quit();
}