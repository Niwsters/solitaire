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
    WindowState state = { false };

    while (state.quit == false)
    {
        lisp_process_queue(app->queue);

        char *card_spec = lisp_get_card();
        Card *card = card_create(card_spec);

        Image *image = card_image(card_suit(card), card_value(card));
        Sprite sprite = { image, card_x(card), card_y(card) };
        window_update(app->window, &state, &sprite);

        card_destroy(card);
    }
}
