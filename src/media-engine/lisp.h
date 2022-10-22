#ifndef LISP_H
#define LISP_H

#include <pthread.h>

#include "queue.h"

pthread_t lisp_start(Queue *queue);
void lisp_receive_message(Queue *queue);

#endif
