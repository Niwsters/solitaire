#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "util.h"

typedef struct Message Message;
struct Message
{
    Message *next;
    char *content;
};

Message *message_create(char *content)
{
    Message *message = malloc(sizeof(Message));
    message->content = content;
    message->next = NULL;
    return message;
}

char *message_content(Message *message)
{
    char *content = malloc(strlen(message->content) + 1);
    strcpy(content, message->content);
    return content;
}

void message_destroy(Message *message)
{
    freen(message);
}

typedef struct
{
    Message *next;
    Message *last;
} Queue;

Queue *queue_create()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->next = NULL;
    queue->last = NULL;
    return queue;
}

void queue_destroy(Queue *queue)
{
    Message *prev;
    Message *next = queue->next;
    while (next != NULL)
    {
        prev = next;
        next = next->next;
        message_destroy(prev);
    }

    freen(queue);
}

char *queue_pop(Queue *queue)
{
    Message *message = queue->next;
    if (message == NULL)
        return NULL;

    queue->next = queue->next->next;
    char *content = message_content(message);
    message_destroy(message);
    return content;
}

void queue_add(Queue *queue, char *content)
{
    Message *message = message_create(content);

    if (queue->last == NULL)
    {
        queue->next = message;
        queue->last = message;
        return;
    }

    queue->last->next = message;
    queue->last = message;
}

void test_message()
{
    Message *message = message_create("oh hi");
    char *content = message_content(message);
    assert(strcmp(content, "oh hi") == 0);
    freen(content);
    message_destroy(message);
}

void test_queue_create()
{
    Queue *queue = queue_create();
    queue_destroy(queue);
}

void test_queue_pop()
{
    Queue *queue = queue_create();
    queue_add(queue, "oh hi");

    char *message = queue_pop(queue);
    assert(strcmp(message, "oh hi") == 0);
    freen(message);

    queue_destroy(queue);
}

void test_queue_pop_empty()
{
    Queue *queue = queue_create();

    char *message = queue_pop(queue);
    assert(message == NULL);

    queue_destroy(queue);
}

void test_queue_add()
{
    Queue *queue = queue_create();
    queue_add(queue, "oh hi");
    queue_add(queue, ":D");
    queue_add(queue, "lolpan");

    char *msg1 = queue_pop(queue);
    char *msg2 = queue_pop(queue);
    char *msg3 = queue_pop(queue);
    assert(strcmp(msg1, "oh hi") == 0);
    assert(strcmp(msg2, ":D") == 0);
    assert(strcmp(msg3, "lolpan") == 0);
    freen(msg1);
    freen(msg2);
    freen(msg3);

    queue_destroy(queue);
}

void queue_test()
{
    test_message();
    test_queue_create();
    test_queue_add();
    test_queue_pop();
    test_queue_pop_empty();

    puts("Tests finished");
}
