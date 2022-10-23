#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

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
    message->content = str(content);
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
    freen(message->content);
    freen(message);
}

typedef struct
{
    Message *next;
    Message *last;
    pthread_mutex_t mutex;
} Queue;

Queue *queue_create()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->next = NULL;
    queue->last = NULL;

    pthread_mutex_init(&queue->mutex, NULL);

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
    pthread_mutex_lock(&queue->mutex);

    Message *message = queue->next;

    char *content = NULL;
    if (message != NULL) {
        queue->next = queue->next->next;
        content = message_content(message);

        if (queue->next == NULL)
            queue->last = NULL;

        message_destroy(message);
    }

    pthread_mutex_unlock(&queue->mutex);

    return content;
}

void queue_add(Queue *queue, char *content)
{
    Message *message = message_create(content);
    pthread_mutex_lock(&queue->mutex);

    if (queue->last == NULL) {
        queue->next = message;
        queue->last = message;
    } else {
        queue->last->next = message;
        queue->last = message;
    }

    pthread_mutex_unlock(&queue->mutex);
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

    char *msg1 = str("oh hi");
    char *msg2 = str(":D");
    char *msg3 = str("lolpan");

    queue_add(queue, msg1);
    queue_add(queue, msg2);
    queue_add(queue, msg3);

    freen(msg1);
    freen(msg2);
    freen(msg3);

    char *result1 = queue_pop(queue);
    char *result2 = queue_pop(queue);
    char *result3 = queue_pop(queue);
    assert(strcmp(result1, "oh hi") == 0);
    assert(strcmp(result2, ":D") == 0);
    assert(strcmp(result3, "lolpan") == 0);
    freen(result1);
    freen(result2);
    freen(result3);

    queue_destroy(queue);
}

void test_queue_add_pop_add()
{
    Queue *queue = queue_create();
    queue_add(queue, "oh hi");
    freen(queue_pop(queue));
    queue_add(queue, ":D");
    queue_destroy(queue);
}

pthread_t thread_create(void *(*func)(void *), void *input)
{
    pthread_t tid;
    pthread_create(&tid, NULL, func, input);
    return tid;
}

void *thread(void *input)
{
    Queue *queue = (Queue*) input;

    // Has a high (not 100%) chance of causing a memory leak if not thread safe
    for (int i=0; i<1000; i++)
        queue_add(queue, "oh hi");

    for (int i=0; i<1000; i++) {
        char *msg = queue_pop(queue);
        if (msg != NULL)
            freen(msg);
    }

    return NULL;
}

void test_queue_multithreaded()
{
    Queue *queue = queue_create();
    pthread_t tid1 = thread_create(thread, queue);
    pthread_t tid2 = thread_create(thread, queue);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    queue_destroy(queue);
}

void queue_run_tests()
{
    puts("Queue: Tests running");

    test_message();
    test_queue_create();
    test_queue_add();
    test_queue_pop();
    test_queue_pop_empty();
    test_queue_add_pop_add();
    test_queue_multithreaded();

    puts("Queue: Tests finished");
}
