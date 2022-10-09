#include <ctype.h>
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

#define PIPE_PATH  "./pipe-test"
#define MESSAGE_LENGTH 10

char BUFFER[80];
char *pipe_next()
{
    /*
    BUFFER[0] = '\0';

    int fd = open(PIPE_PATH, O_RDONLY);

    if (fd == -1)
        puts("WARNING: Failed to open FIFO pipe!");

    read(fd, BUFFER, 80);

    printf("BUFFER: %s\n", BUFFER);
    size_t length = strlen(BUFFER);
    char *msg = calloc(length + 1, sizeof(char));
    strcpy(msg, BUFFER);
    msg[length] = '\0';

    printf("%s\n", msg);

    close(fd);

    return msg;
    */

    FILE *fifo = fopen(PIPE_PATH, "r");

    char c;
    int i=0;
    while ((c = getc(fifo)) != EOF)
    {
        BUFFER[i++] = c;
    }

    size_t length = strlen(BUFFER);
    char *msg = calloc(length, sizeof(char));
    strcpy(msg, BUFFER);

    fclose(fifo);
    printf("msg: %s\n", msg);
    return msg;
}

void pipe_init()
{
    mkfifo(PIPE_PATH, 0666);
}

void pipe_close()
{
}
