#include "getMouse.h"
#include "virtMouse.h"
#include "getCtrl.h"
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <stdbool.h>
#include <poll.h>
#include <stdio.h>
#include <sys/poll.h>

int main()
{
    struct libevdev *dev;
    struct libevdev *kdev;
    struct input_event ev;
    struct input_event kev;
    struct pollfd fds[2];

    char logPath[100];
    char *user = getenv("USER");
    snprintf(logPath, sizeof(logPath), "/home/%s/Documents/kautoscroll_log.txt", user);

    char *mouse = getMouse();
    char *ctrl = getCtrl();

    bool isActive = false;
    int ctrlHold = 0;

    if(mouse && ctrl)
    {
        printf("mouse: %s\n", mouse);
        printf("ctrl: %s\n", ctrl);
        int fd = open(mouse, O_RDONLY);
        int kfd = open(ctrl, O_RDONLY);

        fds[0].fd = fd;
        fds[0].events = POLLIN;
        fds[1].fd = kfd;
        fds[1].events = POLLIN; // notify when data
        
        struct libevdev_uinput *virt = virtMouse();

        libevdev_new_from_fd(fd, &dev);
        libevdev_new_from_fd(kfd, &kdev);

        while (1) 
        {
            poll(fds, 2, -1); // -1 wait forever

            fflush(stdout);

            if(fds[1].revents & POLLIN)
            {
                while(libevdev_next_event(kdev, LIBEVDEV_READ_FLAG_BLOCKING, &kev) >= 0)
                {
                    printf("hello world2");
                    if(kev.code == KEY_LEFTCTRL || kev.code == KEY_RIGHTCTRL)
                    {
                        if(kev.value == 1)
                        {
                            ctrlHold = 1;
                        }

                        if (kev.type == EV_KEY && (kev.code == KEY_LEFTCTRL || kev.code == KEY_RIGHTCTRL) && kev.value == 0)
                        {
                            ctrlHold = 0;
                        }

                        printf("%d \n", ctrlHold);
                    }
                }
            }
            
            if(fds[0].revents & POLLIN)
            {
                while(libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev) >= 0)
                {
                    // printf("hello world");
                    if(ev.type == EV_KEY && ev.code == BTN_MIDDLE && ctrlHold == 1)
                    {
                        printf("Autoscroll enabled\n");
                        
                        isActive = true;
                        if(isActive)
                        {
                            while(libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev) >= 0)
                            {
                                if(ev.type == EV_REL && ev.code == REL_Y)
                                {
                                    printf("Scrolling... ; Value: %d\n", -ev.value);

                                    libevdev_uinput_write_event(virt, EV_REL, REL_WHEEL, -ev.value);
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
        }
        libevdev_uinput_destroy(virt);
        libevdev_free(dev);
        libevdev_free(kdev);
        close(fd);
        close(kfd);
        free(mouse);
        free(ctrl);
    }
}