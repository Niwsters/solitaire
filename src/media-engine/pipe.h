#ifndef PIPE_H
#define PIPE_H

#include <pthread.h>

char *pipe_next();
void pipe_init();
void pipe_close();

#endif
