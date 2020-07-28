#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "card.h"
#include "deck.h"
#include "graphics.h"
#include "debug.h"

static Card *prev_selected_card = NULL;

void handle_click(int x, int y) {
    Card *curr_selected_card = deck_get_card_by_coordinate(x / CARD_SIZE, y / CARD_SIZE);
    if (curr_selected_card == NULL) {
        debug("handle_click: Card id out of bounds");
        return;
    }

    if (prev_selected_card == NULL) {
        // Select card

        debug("Selected card at position %d\n", curr_selected_card->position);
        prev_selected_card = curr_selected_card;
    } else if (prev_selected_card == curr_selected_card) {
        // Rotate card

        debug("Rotated card at position %d\n", curr_selected_card->position);
        deck_rotate_card(curr_selected_card);
        prev_selected_card = NULL;
    } else {
        // Swap cards

        debug("Swap cards at position %d and %d\n", curr_selected_card->position, prev_selected_card->position);
        deck_swap_cards(curr_selected_card, prev_selected_card);
        prev_selected_card = NULL;
    }

}

static void main_loop(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                handle_click(event.button.x, event.button.y);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    debug("Escape pressed\n");
                    prev_selected_card = NULL;
                }
                break;
            default:
                return;
        }
    }

    gfx_draw_screen(prev_selected_card);
}

int main() {
    debug("Starting\n");
    srand(time(NULL));
    deck_init();

    debug("Starting SDL\n");
    SDL_Init(SDL_INIT_VIDEO);
    gfx_init();
    gfx_draw_screen(prev_selected_card);

    debug("Starting emscripten main loop\n");
    emscripten_set_main_loop(&main_loop, 30, 1);

#if 0
       gfx_exit();
       SDL_Quit();
       debug("Exiting\n");
#endif
    return 0;
}

