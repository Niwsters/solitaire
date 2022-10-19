#include <ecl/ecl.h>
#include <ecl/external.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "app.h"
#include "atom.h"
#include "queue.h"

void lisp_interpret_scanf()
{
    printf("> ");
    char msg[128];

    fgets(msg, 128, stdin);

    cl_object result = cl_eval(c_string_to_object(msg));

    ecl_print(result, ECL_T);
    ecl_terpri(ECL_T);
}

void *lisp_loop(void *input)
{
    Queue *queue = (Queue*) input;

    char msg[128];
    while (true) {
        printf("> ");
        fgets(msg, 128, stdin);

        msg[strlen(msg)-1] = '\0'; // trim the enter button

        if (strcmp(msg, "exit") == 0) {
            break;
        }

        queue_add(queue, msg);

        for (int i=0; i<strlen(msg); i++) {
            printf("%i, %i\n", msg[i], isspace(msg[i]));
        }
    }

    return NULL;
}

pthread_t lisp_start(Queue *queue)
{
    /*
    extern void init_lisp(cl_object);
    ecl_init_module(NULL, init_lisp);
    */

    pthread_t tid;
    pthread_create(&tid, NULL, lisp_loop, queue);
    return tid;
}

int main (int argc, char **argv)
{
    cl_boot(argc, argv);

    atom_run_tests();
    queue_run_tests();

    Queue *queue = queue_create();

    pthread_t tid = lisp_start(queue);

    App *app = app_create(queue);
    app_start(app);
    app_destroy(app);

    pthread_join(tid, NULL);

    queue_destroy(queue);

    cl_shutdown();

    exit(0);
    return 0;
}
