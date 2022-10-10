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

typedef struct
{
    const char *path;
} Pipe;

Pipe *pipe_create(const char *path)
{
    Pipe *pipe = malloc(sizeof(Pipe));
    pipe->path = path;
    mkfifo(path, 0666);
    return pipe;
}

const char *pipe_path(Pipe *pipe)
{
    return pipe->path;
}

void pipe_destroy(Pipe *pipe)
{
    remove(pipe_path(pipe));
    freen(pipe);
}

char *pipe_next(Pipe *pipe)
{
    char BUFFER[80] = { '\0' };

    FILE *fifo = fopen(pipe_path(pipe), "r");

    if (!fifo) {
        printf("ERROR: Could not open FIFO file in path %s\n", pipe_path(pipe));
        exit(1);
    }

    char c;
    int length=0;
    while ((c = getc(fifo)) != EOF) {
        BUFFER[length++] = c;
    }

    BUFFER[length++] = '\0';

    char *msg = calloc(length, sizeof(char));
    strcpy(msg, BUFFER);

    fclose(fifo);
    return msg;
}
