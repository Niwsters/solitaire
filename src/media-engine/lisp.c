#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <ecl/ecl.h>

#include "queue.h"
#include "util.h"
#include "list.h"
#include "card_array.h"

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

void lisp_receive_message(char *msg)
{
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
}

void lisp_process_queue(Queue *queue)
{
    char *msg = queue_pop(queue);
    while (msg != NULL) {
        lisp_receive_message(msg);
        freen(msg);
        msg = queue_pop(queue);
    }
}

List *parse(char *card_specs)
{
    List *list = list_create();

    const char *delim = ";";
    char *token = strtok(card_specs, delim);
    while (token != NULL)
    {
        list_add(list, token);
        token = strtok(NULL, delim);
    }

    return list;
}

List *lisp_get_card_specs()
{
    cl_object result = cl_eval(
        c_string_to_object("(logic:get-card)")
    );

    return parse((char*) result->base_string.self);
}

CardArray *lisp_get_cards()
{
    List *specs = lisp_get_card_specs();
    CardArray *card_array = card_array_from_specs(specs);
    list_destroy(specs);
    return card_array;
}
