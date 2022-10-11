#ifndef PIPE_H
#define PIPE_H

#include <pthread.h>

typedef struct Pipe Pipe;
Pipe *pipe_create(const char *path);
char *pipe_next(Pipe *pipe);
void pipe_destroy(Pipe *pipe);
void pipe_send(Pipe *pipe, const char *msg);

#endif
