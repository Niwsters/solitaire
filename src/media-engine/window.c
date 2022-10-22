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

#include "card_image.h"
#include "util.h"
#include "image.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

typedef struct Window
{
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    void (*callback)(struct Window*);
} Window;

typedef void (*Callback)(Window*);

SDL_Renderer *window_renderer(Window *window)
{
    return window->sdl_renderer;
}

void init_sdl() {
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

Window* window_create()
{
    init_sdl();
    init_sdl_image();

    puts("Initialising...");
    Window* window = malloc(sizeof(Window));

    window->sdl_window = create_window();
    puts("Window created");

    window->sdl_renderer = create_renderer(window->sdl_window);
    puts("Renderer created");

    return window;
}

void window_destroy(Window* window)
{
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_DestroyWindow(window->sdl_window);
    SDL_Quit();
    freen(window);
}

void clear_screen(Window *window)
{
    SDL_SetRenderDrawColor(window->sdl_renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderClear(window->sdl_renderer);
}

void window_start(Window *window)
{
    init_card_images(window->sdl_renderer);

    SDL_Event e;
    bool quit = false;
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

        clear_screen(window);

        window->callback(window);

        SDL_RenderPresent(window->sdl_renderer);
        SDL_Delay(1000/60);
    }

    destroy_cards();
}

void window_on_render(Window *window, Callback callback)
{
    window->callback = callback;
}
