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

char *pipe_next()
{
    char BUFFER[80] = { '\0' };

    FILE *fifo = fopen(PIPE_PATH, "r");

    char c;
    int length=0;
    while ((c = getc(fifo)) != EOF)
    {
        BUFFER[length++] = c;
    }

    BUFFER[length++] = '\0';

    char *msg = calloc(length, sizeof(char) + 1);
    strcpy(msg, BUFFER);

    fclose(fifo);
    return msg;
}

void pipe_init()
{
    mkfifo(PIPE_PATH, 0666);
}

void pipe_close()
{
}
