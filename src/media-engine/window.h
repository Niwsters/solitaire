#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "window_state.h"
#include "image.h"
#include "sprite.h"
#include "sprite_array.h"

typedef struct Window Window;
Window* window_create();
void window_destroy(Window* window);
SDL_Renderer *window_renderer(Window *window);
void window_update(Window *window, WindowState *state, SpriteArray *sprites);
void window_render_image(Window *window, Image *image, int x, int y);

#endif
