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
    lisp_interpret_scanf();

    return NULL;
}

pthread_t lisp_start(Atom *atom)
{
    /*
    extern void init_lisp(cl_object);
    ecl_init_module(NULL, init_lisp);
    */

    pthread_t tid;
    pthread_create(&tid, NULL, lisp_loop, NULL);
    return tid;
}

int main (int argc, char **argv)
{
    cl_boot(argc, argv);
    atom_run_tests();
    queue_run_tests();

    /*
    Atom *atom = atom_create("");

    lisp_interpret_scanf();

    App *app = app_create(atom);
    app_start(app);
    app_destroy(app);
    */

    cl_shutdown();

    exit(0);
    return 0;
}
