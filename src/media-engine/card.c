#include <stdlib.h>
#include <string.h>

#include "util.h"

typedef struct
{
    int suit;
    int value;
    int x;
    int y;
} Card;

Card *card_create(char *msg_p)
{
    char *msg = calloc(strlen(msg_p) + 1, sizeof(char));
    strcpy(msg, msg_p);

    Card *card = calloc(1, sizeof(Card));

    const char *delim = " ";

    char *token = strtok(msg, delim);
    char *ptr;
    int parsed[4];
    int i=0;
    while (token != NULL)
    {
        parsed[i++] = strtol(token, &ptr, 10);
        token = strtok(NULL, delim);
    }

    card->suit = parsed[0];
    card->value = parsed[1];
    card->x = parsed[2];
    card->y = parsed[3];

    freen(msg);
    return card;
}

void card_destroy(Card *card)
{
    freen(card);
}

int card_suit(Card *card)
{
    return card->suit;
}

int card_value(Card *card)
{
    return card->value;
}

int card_x(Card *card)
{
    return card->x;
}

int card_y(Card *card)
{
    return card->y;
}
