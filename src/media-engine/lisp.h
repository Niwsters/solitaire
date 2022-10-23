#ifndef LISP_H
#define LISP_H

#include <pthread.h>

#include "queue.h"

pthread_t lisp_start(Queue *queue);
void lisp_process_queue(Queue *queue);
char *lisp_get_card_specs();

#endif
