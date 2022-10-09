#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *texture_load(SDL_Renderer *renderer, SDL_Surface *screen, const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Unable to load image %s. SDL_imge Error: %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(surface);
    
    return texture;
}
