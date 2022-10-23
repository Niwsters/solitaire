#ifndef SPRITE_H
#define SPRITE_H

#include "image.h"
#include "card.h"

typedef struct Sprite Sprite;
Sprite *sprite_from_card(Card *card);
void sprite_destroy(Sprite *sprite);
Image *sprite_image(Sprite *sprite);
int sprite_x(Sprite *sprite);
int sprite_y(Sprite *sprite);


#endif
