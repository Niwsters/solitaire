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

void start()
{
    App *app = app_create();
    init_card_images(app_renderer(app));

    SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
    bool quit = false;
    SDL_Event e;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        app_render(app);

        sleep(1/60);
    }

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
