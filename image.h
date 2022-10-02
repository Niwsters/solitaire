#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL_image.h>

typedef struct Image Image;
Image* image_load(SDL_Renderer *renderer, SDL_Surface *screen, const char* path, int src_x, int src_y, int src_width, int src_height);
void image_render(SDL_Renderer *renderer, Image *image, int x, int y);
void image_destroy(Image *image);

#endif
