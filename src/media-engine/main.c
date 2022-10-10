#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "app.h"
#include "sprite.h"
#include "util.h"
#include "pipe.h"
#include "card.h"
#include "card_image.h"

bool msg_valid(char *msg)
{
    return strlen(msg) > 0;
}

void start()
{
    App *app = app_create();
    init_card_images(app_renderer(app), app_screen(app));

    SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderClear(app_renderer(app));
    SDL_RenderPresent(app_renderer(app));
    bool quit = false;
    SDL_Event e;

    Card *prev = NULL;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(app_renderer(app));

        char *message = pipe_next();
        if (msg_valid(message))
        {
            Card *card = card_create(message);
            app_render_image(app, card_image(card_suit(card), card_value(card)), card_x(card), card_y(card));

            if (prev != NULL)
                card_destroy(prev);

            prev = card;
        }
        freen(message);

        SDL_RenderPresent(app_renderer(app));

        sleep(1/60);
    }
    if (prev != NULL)
        card_destroy(prev);

    destroy_cards();
    app_destroy(app);
}

int main()
{
    pipe_init();
    start();
    pipe_close();

    exit(0);
    return 0;
}
