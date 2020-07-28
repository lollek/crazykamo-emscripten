#include <stdbool.h>
#include <stdlib.h>

#include "card.h"

#include "deck.h"

static Card deck[NUM_CARDS];

void deck_init() {
    bool used_positions[NUM_CARDS] = { 0 };
    for (int i = 0; i < NUM_CARDS; ++i) {
        deck[i].id = i;
        for (;;) {
            int random_position = rand() % NUM_CARDS;
            if (!used_positions[random_position]) {
                used_positions[random_position] = true;
                deck[i].position = random_position;
                break;
            }
        }
        deck[i].rotation = rand() % 4;
    }
}

Card *deck_get_card_by_position(int position) {
    for (int i = 0; i < NUM_CARDS; ++i) {
        if (deck[i].position == position) {
            return &deck[i];
        }
    }
    return NULL;
}

Card *deck_get_card_by_coordinate(int x, int y) {
    return deck_get_card_by_position((y * 3) + x);
}

void deck_rotate_card(Card *card) {
    card->rotation = (card->rotation + 1) % 4;
}

void deck_swap_cards(Card *a, Card *b) {
    int tmp = a->position;
    a->position = b->position;
    b->position = tmp;
}
