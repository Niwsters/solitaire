#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ecl/ecl.h>
#include <ecl/external.h>

#include "util.h"
#include "image.h"
#include "sprite.h"
#include "pipe.h"
#include "card.h"
#include "card_image.h"
#include "atom.h"
#include "queue.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Queue *queue;
} App;

SDL_Renderer *app_renderer(App *app)
{
    return app->renderer;
}

void init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}

void init_sdl_image()
{
    int imgFlags = IMG_INIT_PNG;
    if ( !(IMG_Init(imgFlags) & imgFlags) )
    {
        printf("SDL image could not initialise. SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    puts("Image loading initialised");
}

SDL_Window *create_window()
{
    SDL_Window *window = SDL_CreateWindow(
        "Solitaire",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (window == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf("Unable to load renderer. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    return renderer;
}

App* app_create(Queue *queue)
{
    init_sdl();
    init_sdl_image();

    puts("Initialising...");
    App* app = malloc(sizeof(App));

    app->window = create_window();
    puts("Window created");

    app->renderer = create_renderer(app->window);
    puts("Renderer created");

    app->queue = queue;
    return app;
}

void app_render_image(App *app, Image *image, double x, double y)
{
    image_render(app_renderer(app), image, round(x), round(y));
}

void app_destroy(App* app)
{
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    freen(app);
}

bool msg_valid(char *msg)
{
    return strlen(msg) > 0;
}

void clear_screen(App *app)
{
    SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderClear(app_renderer(app));
}

void app_render(App *app, Card *card)
{
    clear_screen(app);

    app_render_image(
        app,
        card_image(card_suit(card), card_value(card)),
        card_x(card),
        card_y(card)
    );

    SDL_RenderPresent(app_renderer(app));
}

void app_start(App *app)
{
    init_card_images(app_renderer(app));

    SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
    bool quit = false;
    SDL_Event e;

    Card *card = card_create("0 0 0 0");
    while (quit == false)
    {
        char msg[128] = "none";
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
            }
        }

        char *new_msg = queue_pop(app->queue);
        if (new_msg != NULL) {
            cl_object receive_message = cl_eval(
                c_string_to_object("(lambda (msg) (logic:receive-message msg))")
            );

            cl_object result = cl_funcall(
                2,
                receive_message,
                ecl_make_simple_base_string(new_msg, strlen(new_msg))
            );

            ecl_print(result, ECL_T);
            ecl_terpri(ECL_T);

            freen(new_msg);
        }

        app_render(app, card);

        SDL_Delay(1000/60);
    }

    card_destroy(card);
    destroy_cards();
}
