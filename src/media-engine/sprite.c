#include "image.h"
#include "card.h"
#include "card_image.h"
#include "util.h"

typedef struct
{
    Image *image;
    int x;
    int y;
} Sprite;

Sprite *sprite_from_card(Card *card)
{
    Sprite *sprite = calloc(1, sizeof(Sprite));

    sprite->image = card_image(card_suit(card), card_value(card));
    sprite->x = card_x(card);
    sprite->y = card_y(card);

    return sprite;
}

void sprite_destroy(Sprite *sprite)
{
    freen(sprite);
}

Image *sprite_image(Sprite *sprite)
{
    return sprite->image;
}

int sprite_x(Sprite *sprite)
{
    return sprite->x;
}

int sprite_y(Sprite *sprite)
{
    return sprite->y;
}
