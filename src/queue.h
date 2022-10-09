void queue_test();

typedef struct Queue Queue;

Queue *queue_create();

void queue_destroy(Queue *queue);

char *queue_pop(Queue *queue);

void queue_add(Queue *queue, char *content);
