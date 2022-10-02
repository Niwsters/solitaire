#include "util.h"
#include "image.h"

typedef struct
{
    Image *image;
    float x;
    float y;
} Sprite;

Sprite *sprite_create(Image *image)
{
    Sprite *sprite = calloc(1, sizeof(Sprite));
    sprite->image = image;
    sprite->x = 0;
    sprite->y = 0;
    return sprite;
}

void sprite_destroy(Sprite *sprite)
{
    freen(sprite);
}

void sprite_render(SDL_Renderer *renderer, Sprite *sprite)
{
    image_render(renderer, sprite->image, 32, 16);
}
