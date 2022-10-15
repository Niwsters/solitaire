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

#include "util.h"
#include "image.h"
#include "sprite.h"
#include "pipe.h"
#include "card.h"
#include "card_image.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Pipe *pipe_input;
    Pipe *pipe_output;
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

App* app_create()
{
    init_sdl();
    init_sdl_image();

    puts("Initialising...");
    App* app = malloc(sizeof(App));
    app->pipe_input = pipe_create("./pipe-test");
    app->pipe_output = pipe_create("./pipe-io");

    app->window = create_window();
    puts("Window created");

    app->renderer = create_renderer(app->window);
    puts("Renderer created");

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
    pipe_destroy(app->pipe_input);
    pipe_destroy(app->pipe_output);
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

void handle_message(App *app)
{
    char *message = pipe_next(app->pipe_input);
    if (msg_valid(message))
    {
        Card *card = card_create(message);
        app_render_image(app, card_image(card_suit(card), card_value(card)), card_x(card), card_y(card));
        card_destroy(card);
    }
    freen(message);
}

void app_render(App *app)
{
    clear_screen(app);
    //handle_message(app);
    SDL_RenderPresent(app_renderer(app));
}

void app_start(App *app)
{
    init_card_images(app_renderer(app));

    SDL_SetRenderDrawColor(app_renderer(app), 0xFF, 0x00, 0x00, 0x00);
    bool quit = false;
    SDL_Event e;

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
                printf("Mouse: %i, %i\n", x, y);
                sprintf(msg, "mouse_moved %i %i", x, y);
            }
        }
        /*
        puts("Sending message");
        pipe_send(app->pipe_output, msg);
        puts("Message sent");
        */

        app_render(app);

        sleep(1/60);
    }

    destroy_cards();
}
