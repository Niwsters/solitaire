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
#include "list.h"

int main (int argc, char **argv)
{
    queue_run_tests();
    list_run_tests();

    cl_boot(argc, argv);

    extern void init_lisp(cl_object);
    ecl_init_module(NULL, init_lisp);


    Queue *queue = queue_create();

    App *app = app_create(queue);
    app_start(app);
    app_destroy(app);

    queue_destroy(queue);

    cl_shutdown();

    exit(0);
    return 0;
}
