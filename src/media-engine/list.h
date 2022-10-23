#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

void list_run_tests();
typedef struct List List;
List *list_create();
void list_destroy(List *list);
char *list_get(List *list, int index);
void list_add(List *list, char *content);
size_t list_length(List *list);

#endif
