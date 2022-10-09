#ifndef SPRITE_H 
#define SPRITE_H

#include "image.h"

typedef struct Sprite Sprite;
Sprite *sprite_create(Image *image);
void sprite_render(SDL_Renderer *renderer, Sprite *sprite);
void sprite_destroy(Sprite *sprite);

#endif
