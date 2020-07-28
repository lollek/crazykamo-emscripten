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

// TODO: Cards should be rotated on init. And rotate on doubleclick

void handle_click(int x, int y) {
    int prev_selected_card = highlighted_card_id;
    int curr_selected_card = (x / CARD_SIZE) + ((y / CARD_SIZE) * 3);

    if (prev_selected_card == -1) {
        // Select card

        debug("Selected card at position %d\n", curr_selected_card);
        highlighted_card_id = curr_selected_card;
    } else if (prev_selected_card == curr_selected_card) {
        // Rotate card

        debug("Rotated card at position %d\n", curr_selected_card);
        card[curr_selected_card].rotation = (card[curr_selected_card].rotation + 1) % 4;
        highlighted_card_id = -1;
    } else {
        // Swap cards

        debug("Swap cards at position %d and %d\n", curr_selected_card, prev_selected_card);
        int tmp = card[prev_selected_card].position;
        card[prev_selected_card].position = card[curr_selected_card].position;
        card[curr_selected_card].position = tmp;
        highlighted_card_id = -1;
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
                    highlighted_card_id = -1;
                }
                break;
            default:
                return;
        }
    }

    gfx_draw_screen();
}

int main() {
    debug("Starting\n");
    srand(time(NULL));
    deck_init();

    debug("Starting SDL\n");
    SDL_Init(SDL_INIT_VIDEO);
    gfx_init();
    gfx_draw_screen();

    debug("Starting emscripten main loop\n");
    emscripten_set_main_loop(&main_loop, 30, 1);

#if 0
       gfx_exit();
       SDL_Quit();
       debug("Exiting\n");
#endif
    return 0;
}

