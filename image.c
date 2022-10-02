#include <SDL2/SDL_image.h>
#include "app.h"

typedef SDL_Texture Image;

Image* image_load(App* app, const char* path)
{
    SDL_Surface* image_surface = NULL;

    SDL_Surface* loaded = IMG_Load(path);
    if (loaded == NULL)
    {
        printf("Unable to load image %s. SDL_imge Error: %s\n", path, IMG_GetError());
    }
    else
    {
        // Convert PNG Surface to screen Surface for optimisation
        image_surface = SDL_ConvertSurface(loaded, app_surface(app)->format, 0);
        if (image_surface == NULL)
            printf("Unable to optimis image %s. SDL_Error: %s\n", path, SDL_GetError());

        SDL_FreeSurface(loaded);
    }

    SDL_Texture* image = SDL_CreateTextureFromSurface(app_renderer(app), image_surface);
    if (image == NULL)
    {
        printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    SDL_FreeSurface(image_surface);

    return image;
}

void image_render(App *app, Image *image, SDL_Rect *srcrect, SDL_Rect *dstrect)
{
    SDL_RenderCopy(app_renderer(app), image, srcrect, dstrect);
}

void image_destroy(Image *image)
{
    SDL_DestroyTexture(image);
}
