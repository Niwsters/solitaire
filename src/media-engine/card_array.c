#include <stdlib.h>

#include "card.h"
#include "list.h"
#include "util.h"

typedef struct
{
    Card **cards;
    size_t length;
} CardArray;

CardArray *card_array_from_specs(List *specs)
{
    CardArray *list = calloc(1, sizeof(CardArray));

    list->cards = calloc(list_length(specs), sizeof(Card*));
    for (int i=0; i<list_length(specs); i++)
        list->cards[i] = card_create(list_get(specs, i));

    list->length = list_length(specs);
    return list;
}

void card_array_destroy(CardArray *card_array)
{
    for (int i=0; i<card_array->length; i++)
        card_destroy(card_array->cards[i]);
    freen(card_array->cards);
    freen(card_array);
}

Card *card_array_get(CardArray *card_array, int index)
{
    return card_array->cards[index];
}

size_t card_array_length(CardArray *card_array)
{
    return card_array->length;
}
