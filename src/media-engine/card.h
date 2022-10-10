#ifndef CARD_H
#define CARD_H

typedef struct Card Card;
Card *card_create(char *msg);
void card_destroy(Card *card);
int card_suit(Card *card);
int card_value(Card *card);
int card_x(Card *card);
int card_y(Card *card);

#endif
