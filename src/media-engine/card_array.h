#ifndef CARD_ARRAY_H
#define CARD_ARRAY_H

#include "list.h"
#include "card.h"

typedef struct CardArray CardArray;
CardArray *card_array_from_specs(List *specs);
void card_array_destroy(CardArray *card_array);
size_t card_array_length(CardArray *card_array);
Card *card_array_get(CardArray *card_array, int index);

#endif
