#ifndef GETMOUSE_H
#define GETMOUSE_H

#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <dirent.h>
#include <linux/input-event-codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getMouse();

#endif