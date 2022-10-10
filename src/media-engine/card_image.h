#ifndef CARD_IMAGE_H
#define CARD_IMAGE_H

#include "image.h"

void init_card_images(SDL_Renderer *renderer, SDL_Surface *screen);
void destroy_cards();
Image *card_image(int suit, int value);

#endif
