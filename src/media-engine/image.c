#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "texture.h"

typedef struct
{
    SDL_Texture *texture;
    int src_x;
    int src_y;
    int width;
    int height;
} Image;

Image* image_load(SDL_Texture *texture, const char* path, int src_x, int src_y, int width, int height)
{
    Image *image = malloc(sizeof(Image));
    image->texture = texture;
    image->src_x = src_x;
    image->src_y = src_y;
    image->width = width;
    image->height = height;
    return image;
}

void image_render(SDL_Renderer *renderer, Image *image, int x, int y)
{
    SDL_Rect srcrect = { image->src_x, image->src_y, image->width, image->height };
    SDL_Rect dstrect = { x, y, image->width, image->height };
    SDL_RenderCopy(renderer, image->texture, &srcrect, &dstrect);
}

void image_destroy(Image *image)
{
    SDL_DestroyTexture(image->texture);
}
