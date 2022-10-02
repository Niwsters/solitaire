#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *texture_load(SDL_Renderer *renderer, SDL_Surface *screen, const char* path);

#endif
