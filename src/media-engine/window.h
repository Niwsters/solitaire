#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct Window Window;
typedef struct Callback Callback;
Window* window_create();
void window_destroy(Window* window);
void window_start(Window *window);
void window_on_render(Window *window, void (*callback)(Window*));
SDL_Renderer *window_renderer(Window *window);

#endif
