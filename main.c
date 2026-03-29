#include "getMouse.h"
#include "virtMouse.h"
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <linux/input-event-codes.h>
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
        struct libevdev_uinput *virt = virtMouse();
        libevdev_new_from_fd(fd, &dev);

        while (1) 
        {
            fflush(stdout);
            if(libevdev_next_event(dev, LIBEVDEV_READ_FLAG_BLOCKING, &ev) >= 0)
            {
                if(ev.type == EV_KEY && ev.code == BTN_MIDDLE && ev.value == 1 && !isActive)
                {
                    printf("Autoscroll enabled\n");
                    
                    isActive = true;
                    while(isActive)
                    {
                        if (libevdev_next_event(dev, LIBEVDEV_READ_FLAG_BLOCKING, &ev) >= 0){
                            if(ev.type == EV_REL && ev.code == REL_Y)
                            {
                                printf("Scrolling... ; Value: %d\n", ev.value);
                                libevdev_uinput_write_event(virt, EV_REL, REL_WHEEL, ev.value);
                                libevdev_uinput_write_event(virt, EV_SYN, SYN_REPORT, 0);
                            }

                            if (ev.type == EV_KEY && ev.code == BTN_MIDDLE && ev.value == 1 && isActive)
                            {
                                printf("Autoscroll disabled\n");
                                isActive = false;
                            }
                        }
                    }
                }
             }
        }

        free(mouse);
    }
}