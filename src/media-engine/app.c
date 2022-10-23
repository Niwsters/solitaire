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
#include "list.h"
#include "card_array.h"
#include "sprite.h"
#include "sprite_array.h"

typedef struct
{
    Window *window;
    Queue *queue;
} App;

void app_render(Window *window)
{
    Image *image = card_image(0, 0);
    window_render_image(window, image, 0, 0);
}

App* app_create(Queue *queue)
{
    App* app = calloc(1, sizeof(App));

    app->window = window_create(app_render);
    app->queue = queue;

    return app;
}

void app_destroy(App* app)
{
    window_destroy(app->window);
    freen(app);
}

void app_start(App *app)
{
    pthread_t tid = lisp_start(app->queue);

    bool quit = false;
    while (quit == false)
    {
        lisp_process_queue(app->queue);

        CardArray *cards = lisp_get_cards();
        SpriteArray *sprites = sprite_array_from_cards(cards);
        window_update(app->window, &quit, sprites, app->queue);

        sprite_array_destroy(sprites);
        card_array_destroy(cards);
    }
}
