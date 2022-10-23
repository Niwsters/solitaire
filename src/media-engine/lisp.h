#ifndef LISP_H
#define LISP_H

#include <pthread.h>

#include "queue.h"
#include "list.h"
#include "card_array.h"

pthread_t lisp_start(Queue *queue);
void lisp_process_queue(Queue *queue);
CardArray *lisp_get_cards();

#endif
