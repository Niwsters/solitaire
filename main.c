#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "app.h"
#include "image.h"

typedef struct
{
    Image *image;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
} Sprite;

int main()
{
    App* app = app_create();

    Image* image = image_load(app, "./hello_world.png");

    Sprite sprite = {
        image,
        { 0, 0, 128, 128 },
        { 0, 0, 128, 128 }
    };

    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SDL_RenderClear(app_renderer(app));
        image_render(app, image, &sprite.srcrect, &sprite.dstrect);
        SDL_RenderPresent(app_renderer(app));
        sleep(1/60);
    }

    image_destroy(image);
    app_destroy(app);

    return 0;
}
