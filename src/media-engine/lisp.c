#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <ecl/ecl.h>

#include "queue.h"
#include "util.h"

void *repl_loop(void *input)
{
    Queue *queue = (Queue*) input;

    char msg[128];
    while (true) {
        printf("> ");
        fgets(msg, 128, stdin);

        msg[strlen(msg)-1] = '\0'; // trim the enter button

        queue_add(queue, msg);
    }

    return NULL;
}

pthread_t lisp_start(Queue *queue)
{
    pthread_t tid;
    pthread_create(&tid, NULL, repl_loop, queue);
    return tid;
}

void lisp_receive_message(Queue *queue)
{
    char *msg = queue_pop(queue);
    if (msg != NULL) {
        cl_object receive_message = cl_eval(
            c_string_to_object("(lambda (msg) (logic:receive-message msg))")
        );

        cl_object result = cl_funcall(
            2,
            receive_message,
            ecl_make_simple_base_string(msg, strlen(msg))
        );

        ecl_print(result, ECL_T);
        ecl_terpri(ECL_T);

        freen(msg);
    }
}
