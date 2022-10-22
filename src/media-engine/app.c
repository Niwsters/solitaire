#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include "util.h"
#include "image.h"
#include "card.h"
#include "card_image.h"
#include "queue.h"
#include "lisp.h"
#include "window.h"

typedef struct
{
    Window *window;
    Queue *queue;
} App;

App* app_create(Queue *queue)
{
    App* app = malloc(sizeof(App));

    app->window = window_create();
    app->queue = queue;

    return app;
}

void app_destroy(App* app)
{
    window_destroy(app->window);
    freen(app);
}

void app_render(Window *window)
{
    Image *image = card_image(0, 0);
    image_render(window_renderer(window), image, 0, 0);
}

void app_start(App *app)
{
    window_on_render(app->window, app_render);
    window_start(app->window);
}
