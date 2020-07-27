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

// TODO: Cards should be rotated on init. And rotate on doubleclick

void handle_click(int x, int y) {
    int prev_selected_card = highlighted_card_id;
    int curr_selected_card = (x / CARD_SIZE) + ((y / CARD_SIZE) * 3);

    if (prev_selected_card == -1) {
        // Select card

        highlighted_card_id = curr_selected_card;
    } else if (prev_selected_card == curr_selected_card) {
        // Rotate card

        card[curr_selected_card].rotation = (card[curr_selected_card].rotation + 1) % 4;
        highlighted_card_id = -1;
    } else {
        // Swap cards

        int tmp = card[prev_selected_card].position;
        card[prev_selected_card].position = card[curr_selected_card].position;
        card[curr_selected_card].position = tmp;
        highlighted_card_id = -1;
    }

}

EM_BOOL main_loop(double time, void *userdata) {
    SDL_Event event;
    bool has_pending_event = SDL_PollEvent(&event) != 0;
    if (has_pending_event) {
        return EM_TRUE;
    }

    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            handle_click(event.button.x, event.button.y);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                highlighted_card_id = -1;
            }
            break;
        default:
            return EM_TRUE;
    }


    gfx_draw_screen();
    return EM_TRUE;
}

int main() {
    srand(time(NULL));
    deck_init();

    SDL_Init(SDL_INIT_VIDEO);
    gfx_init();
    gfx_draw_screen();

    emscripten_request_animation_frame_loop(main_loop, NULL);
#if 0
#ifdef __EMCRIPTEN__
#else
    bool running = true;
    while (running) {
        running = main_loop(0, NULL);
    }
#endif


    gfx_exit();
    SDL_Quit();
#endif
    return 0;
}

