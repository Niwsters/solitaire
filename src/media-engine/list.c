#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "util.h"

typedef struct Node Node;
struct Node
{
    Node *next;
    char *content;
};

Node *node_create(char *content)
{
    Node *node = calloc(1, sizeof(Node));
    node->content = content;
    node->next = NULL;
    return node;
}

char *node_content(Node *node)
{
    char *content = calloc(strlen(node->content) + 1, sizeof(char));
    strcpy(content, node->content);
    return content;
}

void node_destroy(Node *node)
{
    freen(node);
}

typedef struct
{
    Node *first;
    Node *last;
    size_t length;
} List;

List *list_create()
{
    List *list = calloc(1, sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

void list_destroy(List *list)
{
    Node *node = list->first;
    while (node != NULL) {
        Node *to_destroy = node;
        node = node->next;
        node_destroy(to_destroy);
    }
    list->last = NULL;
    freen(list);
}

char *list_get(List *list, int index)
{
    if (list->first == NULL)
        return str("");

    Node *current = list->first;
    for (int i=0; i<index; i++) {
        if (current->next == NULL) {
            printf("ERROR: Index out of range: %i\n", index);
            assert(current->next);
        }
        current = current->next;
    }

    return current->content;
}

void list_add(List *list, char *content)
{
    assert(content);
    Node *node = node_create(content);
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    list->length += 1;
}

size_t list_length(List *list)
{
    return list->length;
}

void list_test_create()
{
    List *list = list_create();
    list_destroy(list);
}

void list_test_add()
{
    List *list = list_create();
    list_add(list, "oh hi");
    list_add(list, ":D");
    list_add(list, "blargh");

    assert(strcmp(list_get(list, 0), "oh hi") == 0);
    assert(strcmp(list_get(list, 1), ":D") == 0);
    assert(strcmp(list_get(list, 2), "blargh") == 0);

    assert(list_length(list) == 3);

    list_destroy(list);
}

void list_run_tests()
{
    puts("List: Tests running");

    list_test_create();
    list_test_add();

    puts("List: Tests finished");
}
