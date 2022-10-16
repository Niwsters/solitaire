typedef struct Queue Queue;
Queue *queue_create();
void queue_destroy(Queue *queue);
char *queue_pop(Queue *queue);
void queue_add(Queue *queue, char *content);
void queue_run_tests();
