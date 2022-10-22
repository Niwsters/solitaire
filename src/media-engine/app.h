#ifndef APP_H
#define APP_H

#include "queue.h"

typedef struct App App;
App* app_create(Queue *queue);
void app_destroy(App* app);
void app_start(App *app);

#endif
