#include <ecl/ecl.h>
#include <ecl/external.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "app.h"
#include "pipe.h"
#include "util.h"

typedef struct
{
    char *value;
    pthread_mutex_t mutex;
} Atom;

Atom *atom_create(char *value)
{
    Atom *atom = calloc(1, sizeof(Atom));

    size_t length = strlen(value) + 1;
    atom->value = calloc(length, sizeof(char));
    strcpy(atom->value, value);

    pthread_mutex_init(&atom->mutex, NULL);

    return atom;
}

void atom_destroy(Atom **atom)
{
    assert(atom);
    if (*atom) {
        Atom *self = *atom;
        freen(self->value);
        freen(self);
    }
}

char *atom_value(Atom *atom)
{
    pthread_mutex_lock(&atom->mutex);

    char *value = calloc(strlen(atom->value)+1, sizeof(char));
    strcpy(value, atom->value);

    pthread_mutex_unlock(&atom->mutex);

    return value;
}

void atom_swap(Atom *atom, char *(*value_func)(char*))
{
    pthread_mutex_lock(&atom->mutex);

    char *new_value = value_func(atom->value);
    freen(atom->value);
    atom->value = new_value;

    pthread_mutex_unlock(&atom->mutex);
}

char *add_honk(char *str)
{
    size_t length = strlen(str) + strlen(" honk");
    char *new = calloc(length + 1, sizeof(char));
    strcpy(new, str);
    strcat(new, " honk");
    return new;
}

void *test(void *atom_p)
{
    Atom *atom = (Atom*) atom_p;

    char *value = atom_value(atom);
    printf("Atom: %s\n", value);
    freen(value);
    atom_swap(atom, add_honk);

    char *value2 = atom_value(atom);
    printf("Atom: %s\n", value2);
    freen(value2);

    return NULL;
}

pthread_t thread_create(void *(*func)(void*), void *input)
{
    pthread_t tid;
    pthread_create(&tid, NULL, func, input);
    return tid;
}

void *await_user_input(void *input)
{
    Atom *atom = (Atom*) input;

    while (strcmp(atom_value(atom), "true") != 0);

    char msg[128];

    printf("Type msg plz: ");
    scanf("%s", msg);

    printf("msg: %s\n", msg);

    return NULL;
}

char *set_true(char *current)
{
    return "true";
}

int main (int argc, char **argv)
{
    /*
    Atom *atom = atom_create("blargh");

    pthread_t t1 = thread_create(atom);
    pthread_t t2 = thread_create(atom);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    atom_destroy(&atom);

    cl_boot(argc, argv);
    extern void init_lisp(cl_object);
    ecl_init_module(NULL, init_lisp);

    cl_object fun_receive_message = cl_eval(c_string_to_object("(lambda (msg) (receive-message msg))"));
    const char *msg = "oh hi :D";
    cl_object result = cl_funcall(2, fun_receive_message, ecl_make_constant_base_string(msg, strlen(msg)));
    */

    Atom *atom = atom_create("false");
    pthread_t tid = thread_create(&await_user_input, atom);

    App *app = app_create();
    atom_swap(atom, set_true);
    app_start(app);
    app_destroy(app);

    pthread_join(tid, NULL);

    /*
    cl_shutdown();
    */
    exit(0);
    return 0;
}
