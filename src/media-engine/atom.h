#ifndef ATOM_H
#define ATOM_H

typedef struct Atom Atom;
Atom *atom_create(char *value);
void atom_destroy(Atom **atom);
char *atom_value(Atom *atom);
void atom_swap(Atom *atom, char *(*value_func)(char*));
void atom_run_tests();

#endif
