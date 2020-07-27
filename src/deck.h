#ifndef DECK_H
#define DECK_H

#include "card.h"

#define NUM_CARDS 9
#define CARDS_PER_ROW 3
#define CARDS_PER_COLUMN 3

extern Card card[NUM_CARDS];

// [0-8] if a card should be highlighted. Else it is -1
extern int highlighted_card_id;

void deck_init();

#endif /* DECK_H */
