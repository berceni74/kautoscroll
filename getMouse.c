#include "getMouse.h"
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <dirent.h>
#include <linux/input-event-codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getMouse()
{
    DIR *dirp = opendir("/dev/input");
    struct dirent *file;
    struct libevdev *dev;

    while((file = readdir(dirp)) != NULL) 
    {
        if(file->d_type == DT_CHR)
        {
            if(strncmp(file->d_name, "event", 5) == 0)
            {
                char *path = malloc(30);
                snprintf(path, 30, "/dev/input/%s", file->d_name);
                int fd = open(path, O_RDONLY);
                
                libevdev_new_from_fd(fd, &dev);

                if (libevdev_has_event_code(dev, EV_KEY, BTN_MIDDLE))
                {
                    libevdev_free(dev);
                    close(fd);
                    closedir(dirp);
                    return path;
                }

                libevdev_free(dev);
                close(fd);
            }
        }
    }
    closedir(dirp);
    return NULL;
}