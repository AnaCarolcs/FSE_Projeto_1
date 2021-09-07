#include "log.h"

void create_csv()
{
    FILE *file = fopen("log.csv", "w");

    fprintf(file, "DATETIME, INTERNA, EXTERNA, REFERENCIA, CONTROLE\n");

    fclose(file);
}

const char *get_time_info()
{
    static char timestamp[20];
    time_t mytime;

    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    sprintf(timestamp, "%02d-%02d-%02d-%02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1,
            tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return timestamp;
}

void write_on_log(temperature_info temp, int controle)
{
    FILE *file = fopen("log.csv", "a");

    fprintf(file, "%s,%f,%f,%d,%d\n", get_time_info(), temp.interna,
            temp.externa, temp.referencia, controle);
    fclose(file);
}