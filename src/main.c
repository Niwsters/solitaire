#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "app.h"
#include "sprite.h"
#include "image.h"
#include "util.h"
#include "texture.h"


enum CARD_SUIT
{
    SUIT_CLUBS,
    SUIT_DIAMONDS,
    SUIT_HEARTS,
    SUIT_SPADES,
    SUIT_MISC
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
    VALUE_KING
};

const int CARD_WIDTH = 158;
const int CARD_HEIGHT = 246;

typedef Image Card;

Image *create_card(SDL_Texture *texture, int suit, int value)
{
    return image_load(texture, "./data/bonded.png", CARD_WIDTH*value, CARD_HEIGHT*suit, CARD_WIDTH, CARD_HEIGHT);
}


Image *CARDS[4][13];
void load_cards(SDL_Texture *texture)
{
    for (int suit=0; suit<4; suit++)
    for (int value=0; value<13; value++)
        CARDS[suit][value] = create_card(texture, suit, value);
}

void destroy_cards()
{
    for (int suit=0; suit<4; suit++)
    for (int value=0; value<13; value++)
        image_destroy(CARDS[suit][value]);
}

Image *card_image(int suit, int value)
{
    return CARDS[suit][value];
}

int main()
{
    App *app = app_create();

    SDL_Texture *texture = texture_load(app_renderer(app), app_screen(app), "./data/bonded.png");
    load_cards(texture);

    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(app_renderer(app));
        app_render_image(app, card_image(SUIT_SPADES, VALUE_ACE), 0, 0);
        app_render_image(app, card_image(SUIT_HEARTS, VALUE_KING), 100, 200);
        SDL_RenderPresent(app_renderer(app));
        sleep(1/60);
    }

    destroy_cards();
    app_destroy(app);

    return 0;
}
