#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

void atom_test_create()
{
    Atom *atom = atom_create("blargh");
    atom_destroy(&atom);
}

void atom_test_value()
{
    Atom *atom = atom_create("blargh");

    char *value = atom_value(atom);
    assert(strcmp(value, "blargh") == 0);
    freen(value);

    atom_destroy(&atom);
}

char *test_set_honk(char *current)
{
    char *new = calloc(strlen("honk") + 1, sizeof(char));
    strcpy(new, "honk");
    return new;
}

void atom_test_swap()
{
    Atom *atom = atom_create("blargh");

    atom_swap(atom, test_set_honk);

    char *value = atom_value(atom);
    assert(strcmp(value, "honk") == 0);
    freen(value);

    atom_destroy(&atom);
}

typedef struct
{
    char *value;
} Object;

void atom_run_tests()
{
    printf("Running Atom tests\n");

    atom_test_create();
    atom_test_value();
    atom_test_swap();

    printf("Atom tests finished\n");
}
