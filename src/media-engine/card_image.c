#include "image.h"
#include "texture.h"

enum CARD_SUIT
{
    SUIT_CLUBS,
    SUIT_DIAMONDS,
    SUIT_HEARTS,
    SUIT_SPADES,
    SUIT_MISC,
    SUIT_COUNT
};

enum CARD_VALUE
{
    VALUE_ACE,
    VALUE_TWO,
    VALUE_THREE,
    VALUE_FOUR,
    VALUE_FIVE,
    VALUE_SIX,
    VALUE_SEVEN,
    VALUE_EIGHT,
    VALUE_NINE,
    VALUE_TEN,
    VALUE_JACK,
    VALUE_QUEEN,
    VALUE_KING,
    VALUE_COUNT
};

const int CARD_WIDTH = 158;
const int CARD_HEIGHT = 246;

Image *create_card_image(SDL_Texture *texture, int suit, int value)
{
    return image_load(texture, "./data/bonded.png", CARD_WIDTH*value, CARD_HEIGHT*suit, CARD_WIDTH, CARD_HEIGHT);
}

Image *CARDS[4][13];
void load_cards(SDL_Texture *texture)
{
    for (int suit=0; suit<4; suit++)
    for (int value=0; value<13; value++)
        CARDS[suit][value] = create_card_image(texture, suit, value);
}

void init_card_images(SDL_Renderer *renderer, SDL_Surface *screen)
{
    SDL_Texture *texture = texture_load(renderer, screen, "./data/bonded.png");
    puts("Texture loaded");
    load_cards(texture);
    puts("Cards loaded");
}

void destroy_cards()
{
    for (int suit=0; suit<4; suit++)
    for (int value=0; value<13; value++)
        image_destroy(CARDS[suit][value]);
}

Image *card_image(int suit, int value)
{
    if (suit > SUIT_COUNT - 1)
        return CARDS[SUIT_CLUBS][VALUE_ACE];

    return CARDS[suit][value];
}
