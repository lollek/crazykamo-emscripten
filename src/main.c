#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "card.h"
#include "deck.h"
#include "graphics.h"

// TODO: Cards should be rotated on init. And rotate on doubleclick

int main() {
    srand(time(NULL));
    deck_init();

    gfx_init();


    //for (;;) {
        gfx_draw_screen();
    //}


    gfx_exit();
    return 0;
}

