#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "app.h"
#include "sprite.h"
#include "image.h"
#include "util.h"
#include "texture.h"
#include "pipe.h"


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

void *input(void *vargp)
{
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
        sleep(1/60);
    }

    return NULL;
}

void *loop(void *vargp)
{
    App *app = app_create();
    SDL_Texture *texture = texture_load(app_renderer(app), app_screen(app), "./data/bonded.png");
    load_cards(texture);

    while (true)
    {
        char *msg = pipe_next();
        if (strlen(msg) > 0)
            printf("SBCL: %s\n", msg);
        freen(msg);

        SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(app_renderer(app));
        app_render_image(app, card_image(SUIT_SPADES, VALUE_ACE), 0, 0);
        app_render_image(app, card_image(SUIT_HEARTS, VALUE_KING), 100, 200);
        SDL_RenderPresent(app_renderer(app));
        sleep(1/60);
    }

    destroy_cards();
    app_destroy(app);
    return NULL;
}

pthread_t create_thread(void (*func), void *input)
{
    pthread_t thread;
    pthread_create(&thread, NULL, func, input);
    return thread;
}

int main()
{
    pthread_t thread_input = create_thread(input, NULL);
    pthread_t thread_loop = create_thread(loop, NULL);

    pthread_join(thread_input, NULL);

    exit(0);
    return 0;
}
