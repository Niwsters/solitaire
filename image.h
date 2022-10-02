#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL_image.h>
#include "app.h"

typedef struct Image Image;
Image* image_load(App* app, const char* path);
void image_render(App *app, Image *image, SDL_Rect *srcrect, SDL_Rect *dstrect);
void image_destroy(Image *image);

#endif
