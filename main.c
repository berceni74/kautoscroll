#include "clogger/clogger.h"
#include "getMouse.h"
#include <stdbool.h>

int main()
{
    struct libevdev *dev;
    struct input_event ev;

    char logPath[100];
    char *user = getenv("USER");
    snprintf(logPath, sizeof(logPath), "/home/%s/Documents/kautoscroll_log.txt", user);
    char *mouse = getMouse();
    bool isActive = false;

    if(mouse)
    {
        int fd = open(mouse, O_RDONLY);
        libevdev_new_from_fd(fd, &dev);

        while (1) 
        {
            if(libevdev_next_event(dev, LIBEVDEV_READ_FLAG_BLOCKING, &ev) >= 0)
            {
                if(ev.type == EV_KEY && ev.code == BTN_MIDDLE && ev.value == 1 && !isActive)
                {
                    cclogg(logPath, GREEN, "ENABLE", "Autoscroll enabled", false);
                    fflush(stdout);
                    isActive = true;
                }
                else if (ev.type == EV_KEY && ev.code == BTN_MIDDLE && ev.value == 1 && isActive)
                {
                    cclogg(logPath, RED, "DISABLE", "Autoscroll disabled", false);
                    fflush(stdout);
                    isActive = false;
                }
             }
        }

        free(mouse);
    }
}