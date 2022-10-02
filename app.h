#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

typedef struct App App;
App* app_create();
void app_destroy(App* app);
SDL_Window *app_window(App *app);
SDL_Surface *app_surface(App *app);
SDL_Renderer *app_renderer(App *app);

#endif
