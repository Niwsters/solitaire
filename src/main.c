#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "app.h"
#include "sprite.h"
#include "image.h"
#include "util.h"

int main()
{
    App *app = app_create();

    Image *image = image_load(app_renderer(app), app_screen(app), "./bonded.png", 0, 0, 158, 245);
    Sprite *sprite = sprite_create(image);

    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(app_renderer(app));
        app_render_sprite(app, sprite);
        SDL_RenderPresent(app_renderer(app));
        sleep(1/60);
    }

    image_destroy(image);
    sprite_destroy(sprite);
    app_destroy(app);

    return 0;
}
