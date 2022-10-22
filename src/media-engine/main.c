#include <ecl/ecl.h>
#include <ecl/external.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "app.h"
#include "queue.h"
#include "lisp.h"

int main (int argc, char **argv)
{
    cl_boot(argc, argv);

    extern void init_lisp(cl_object);
    ecl_init_module(NULL, init_lisp);

    queue_run_tests();

    Queue *queue = queue_create();

    pthread_t tid = lisp_start(queue);

    App *app = app_create(queue);
    app_start(app);
    app_destroy(app);

    queue_destroy(queue);

    cl_shutdown();

    exit(0);
    return 0;
}
