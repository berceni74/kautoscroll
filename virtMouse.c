#include "virtMouse.h"

struct libevdev_uinput *virtMouse()
{
    struct libevdev *dev;
    struct libevdev_uinput *uidev;

    dev = libevdev_new();
    libevdev_set_name(dev, "scroll mouse");
    libevdev_enable_event_type(dev, EV_REL);
    libevdev_enable_event_code(dev, EV_REL, REL_WHEEL, NULL);
    libevdev_enable_event_code(dev, EV_REL, REL_X, NULL);
    libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);
    libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);

    return uidev;
}