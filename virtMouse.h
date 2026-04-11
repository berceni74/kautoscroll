#ifndef VIRTMOUSE_H
#define VIRTMOUSE_H

#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <unistd.h>

struct libevdev_uinput *virtMouse();

#endif