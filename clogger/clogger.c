#include "clogger.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

void clogg(char *log, char *type, char *content, bool print)
{
    time_t logTime;
    time(&logTime);

    FILE *file = fopen(log, "a+");
    if(file == NULL)
    {
        perror("fopen");
        return;
    }

    fprintf(file, "[%s] %s | %s", type, content, ctime(&logTime));

    if(print)
    {
        printf("[%s] %s | %s", type, content, ctime(&logTime));
    }

    fflush(file);
    fflush(stdout);
    fclose(file);
}

void cclogg(char *log, char *color, char *type, char *content, bool print)
{
    time_t logTime;
    time(&logTime);

    FILE *file = fopen(log, "a+");
    if(file == NULL)
    {
        perror("fopen");
        return;
    }

    fprintf(file, "[%s] %s | %s", type, content, ctime(&logTime));

    if(print)
    {
        printf("[%s%s\033[0m] %s | %s", color, type, content, ctime(&logTime));
    }

    fflush(file);
    fflush(stdout);
    fclose(file);
}