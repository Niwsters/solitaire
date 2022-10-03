#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "util.h"

const char *pipe_path = "./pipe-test";

char BUFFER[80];
char *pipe_next()
{
    int fd = open(pipe_path, O_RDONLY);
    read(fd, BUFFER, sizeof(BUFFER));
    close(fd);

    char *msg = malloc(strlen(BUFFER));
    strcpy(msg, BUFFER);
    return msg;
}

void *pipe_read(void *vargp)
{
    while (true)
    {
        char *msg = pipe_next();
        printf("Pipe: %s\n", msg);
        freen(msg);

        sleep(1/60);
    }
    return NULL;
}

void pipe_init()
{
    mkfifo(pipe_path, 0666);
}
