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

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
} App;

SDL_Window *app_window(App *app)
{
    return app->window;
}

SDL_Surface *app_screen(App *app)
{
    return SDL_GetWindowSurface(app_window(app));
}

SDL_Renderer *app_renderer(App *app)
{
    return app->renderer;
}

App* app_create()
{
    App* app = malloc(sizeof(App));

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    puts("Creating window");

    app->window = SDL_CreateWindow(
        "Solitaire",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    puts("Window created");

    if (app->window == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    int imgFlags = IMG_INIT_PNG;
    if ( !(IMG_Init(imgFlags) & imgFlags) )
    {
        printf("SDL image could not initialise. SDL_image Error: %s\n", IMG_GetError());
        return NULL;
    }

    puts("Image loading initialised");

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->renderer == NULL)
    {
        printf("Unable to load renderer. SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    puts("App created");

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
