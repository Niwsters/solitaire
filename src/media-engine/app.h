#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "image.h"
#include "sprite.h"

typedef struct App App;
App* app_create();
void app_destroy(App* app);
SDL_Renderer *app_renderer(App *app);
void app_render(App *app);
void app_start(App *app);

#endif
