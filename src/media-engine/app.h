#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "image.h"
#include "sprite.h"

typedef struct App App;
App* app_create();
void app_destroy(App* app);
SDL_Window *app_window(App *app);
SDL_Surface *app_screen(App *app);
SDL_Renderer *app_renderer(App *app);
void app_render_image(App *app, Image *image, double x, double y);

#endif
