#include "getMouse.h"
#include <stdbool.h>
#include <stdio.h>

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
                    printf("Autoscroll enabled\n");
                    fflush(stdout);
                    isActive = true;
                }
                else if (ev.type == EV_KEY && ev.code == BTN_MIDDLE && ev.value == 1 && isActive)
                {
                    printf("Autoscroll disabled\n");
                    fflush(stdout);
                    isActive = false;
                }
             }
        }

        free(mouse);
    }
}