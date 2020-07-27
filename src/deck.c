#include <stdbool.h>
#include <stdlib.h>

#include "card.h"

#include "deck.h"

Card card[NUM_CARDS];

void deck_init() {
    bool used_positions[NUM_CARDS] = { 0 };
    for (int i = 0; i < NUM_CARDS; ++i) {
        card[i].id = i;
        for (;;) {
            int random_position = rand() % NUM_CARDS;
            if (!used_positions[random_position]) {
                used_positions[random_position] = true;
                card[i].position = random_position;
                break;
            }
        }
        card[i].rotation = rand() % 4;
    }
}
