#ifndef SPRITE_ARRAY_H
#define SPRITE_ARRAY_H

#include <stdlib.h>

#include "card_array.h"
#include "sprite.h"

typedef struct SpriteArray SpriteArray;
SpriteArray *sprite_array_from_cards(CardArray *card_array);
void sprite_array_destroy(SpriteArray *list);
Sprite *sprite_array_get(SpriteArray *sprite_array, int index);
size_t sprite_array_length(SpriteArray *sprite_array);

#endif
