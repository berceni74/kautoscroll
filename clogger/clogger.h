#ifndef CLOGGER_H
#define CLOGGER_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#define RED    "\x1b[31m"
#define YELLOW "\x1b[33m"
#define GREEN  "\x1b[32m"

void clogg(char *log, char *type, char *content, bool print);
void cclogg(char *log, char* color, char *type, char *content, bool print);

#endif