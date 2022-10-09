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
#include "queue.h"


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
    if (suit > SUIT_COUNT - 1)
        return CARDS[SUIT_CLUBS][VALUE_ACE];

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

typedef struct
{
    int suit;
    int value;
    int x;
    int y;
} Card;

Card *card_create(char *msg)
{
    Card *card = calloc(1, sizeof(Card));

    const char *delim = " ";

    char *token = strtok(msg, delim);
    char *ptr;
    int parsed[4];
    int i=0;
    while (token != NULL)
    {
        parsed[i++] = strtol(token, &ptr, 10);
        token = strtok(NULL, delim);
    }

    card->suit = parsed[0];
    card->value = parsed[1];
    card->x = parsed[2];
    card->y = parsed[3];

    return card;
}

void card_destroy(Card *card)
{
    freen(card);
}

bool msg_valid(char *msg)
{
    return strlen(msg) > 0;
}

void start()
{
    App *app = app_create();
    SDL_Texture *texture = texture_load(app_renderer(app), app_screen(app), "./data/bonded.png");
    puts("Texture loaded");
    load_cards(texture);
    puts("Cards loaded");

    SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderClear(app_renderer(app));
    SDL_RenderPresent(app_renderer(app));
    bool quit = false;
    SDL_Event e;

    Card *prev = NULL;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(app_renderer(app));

        char *message = pipe_next();
        if (msg_valid(message))
        {
            Card *card = card_create(message);
            app_render_image(app, card_image(card->suit, card->value), card->x, card->y);

            if (prev != NULL)
                card_destroy(prev);

            prev = card;
        }
        else
        {
            /*
            if (prev != NULL)
                app_render_image(app, card_image(prev->suit, prev->value), prev->x, prev->y);
                */
        }
        freen(message);

        SDL_RenderPresent(app_renderer(app));

        sleep(1/60);
    }
    if (prev != NULL)
        card_destroy(prev);

    destroy_cards();
    app_destroy(app);
}

pthread_t create_thread(void (*func), void *input)
{
    pthread_t thread;
    pthread_create(&thread, NULL, func, input);
    return thread;
}

int main()
{
    queue_test();

    pipe_init();
    start();
    pipe_close();

    exit(0);
    return 0;
}
