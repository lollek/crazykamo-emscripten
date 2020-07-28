#ifndef DECK_H
#define DECK_H

#include "card.h"

#define NUM_CARDS 9
#define CARDS_PER_ROW 3
#define CARDS_PER_COLUMN 3

void deck_init();

/**
 * deck_get_card_by_position
 * @position    Visual position on the board [0-8]
 *
 * Returns the card on a given visual position, where the position is
 * 0 1 2
 * 3 4 5
 * 6 7 8
 */
Card *deck_get_card_by_position(int position);

/**
 * deck_get_card_by_coordinate
 * @x       x coordinate on the board [0-2]
 * @y       y coordinate on the board [0-2]
 *
 * Returns the Card on the given tile. Not the graphical x/y.
 */
Card *deck_get_card_by_coordinate(int x, int y);

/**
 * deck_rotate_card
 * @card    Card to rotate
 *
 * Rotate card by 90 degrees
 */

void deck_rotate_card(Card *card);

/**
 * deck_swap_cards
 * 
 * Swaps the position of cards a and b
 */
void deck_swap_cards(Card *a, Card *b);

#endif /* DECK_H */
