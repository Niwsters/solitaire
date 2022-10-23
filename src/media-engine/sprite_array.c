#include "sprite.h"
#include "card_array.h"
#include "util.h"

typedef struct
{
    Sprite **sprites;
    size_t length;
} SpriteArray;

SpriteArray *sprite_array_from_cards(CardArray *card_array)
{
    SpriteArray *sprite_array = calloc(1, sizeof(SpriteArray));

    Sprite **sprites;
    sprites = calloc(card_array_length(card_array), sizeof(Sprite*));
    for (int i=0; i<card_array_length(card_array); i++)
        sprites[i] = sprite_from_card(card_array_get(card_array, i));

    sprite_array->sprites = sprites;
    sprite_array->length = card_array_length(card_array);

    return sprite_array;
}

void sprite_array_destroy(SpriteArray *list)
{
    for (int i=0; i<list->length; i++)
        sprite_destroy(list->sprites[i]);
    freen(list->sprites);
    freen(list);
}

Sprite *sprite_array_get(SpriteArray *sprite_array, int index)
{
    return sprite_array->sprites[index];
}

size_t sprite_array_length(SpriteArray *sprite_array)
{
    return sprite_array->length;
}
