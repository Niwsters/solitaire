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
#include "window_state.h"
#include "list.h"

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

List *parse(char *card_specs)
{
    List *list = list_create();

    const char *delim = ";";
    char *token = strtok(card_specs, delim);
    while (token != NULL)
    {
        list_add(list, token);
        token = strtok(NULL, delim);
    }

    return list;
}

void app_start(App *app)
{
    WindowState state = { false };

    Sprite sprite = { card_image(0, 0), 0, 0 };
    while (state.quit == false)
    {
        lisp_process_queue(app->queue);

        char *card_specs = lisp_get_card_specs();
        List *specs = parse(card_specs);
        Card *cards[list_length(specs)];
        for (int i=0; i<list_length(specs); i++)
            cards[i] = card_create(list_get(specs, i));

        Sprite *sprites[list_length(specs)];
        for (int i=0; i<list_length(specs); i++) {
            Card *card = cards[i];
            Image *image = card_image(card_suit(card), card_value(card));
            Sprite *sprite = calloc(1, sizeof(Sprite));
            sprite->image = image;
            sprite->x = card_x(card);
            sprite->y = card_y(card);
            sprites[i] = sprite;
        }

        for (int i=0; i<list_length(specs); i++) {
            card_destroy(cards[i]);
        }

        window_update(app->window, &state, sprites, list_length(specs));

        for (int i=0; i<list_length(specs); i++) {
            freen(sprites[i]);
        }

        list_destroy(specs);
    }
}
