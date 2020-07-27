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

// TODO: Cards should be rotated on init. And rotate on doubleclick

size_t const CARD_SIZE = 150;
size_t const CANVAS_WIDTH = CARD_SIZE * CARDS_PER_ROW;
size_t const CANVAS_HEIGHT = CARD_SIZE * CARDS_PER_ROW;

SDL_Renderer* renderer;
SDL_Texture* image;

SDL_Texture* load_texture(SDL_Renderer* renderer, char const* const path) {
    SDL_Surface* image = IMG_Load(path);
    if (!image)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        return 0;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return tex;
}




void draw_screen() {
    SDL_RenderClear(renderer);

    for (int i = 0; i < NUM_CARDS; ++i) {
        SDL_Rect const src = {
            .x = (card[i].id % CARDS_PER_ROW) * CARD_SIZE,
            .y = (card[i].id / CARDS_PER_ROW) * CARD_SIZE,
            .w = CARD_SIZE,
            .h = CARD_SIZE,
        };
        SDL_Rect const dst = {
            .x = (card[i].position % CARDS_PER_ROW) * CARD_SIZE,
            .y = (card[i].position / CARDS_PER_ROW) * CARD_SIZE,
            .w = CARD_SIZE,
            .h = CARD_SIZE,
        };
        SDL_RenderCopy (renderer, image, &src, &dst);
    }

    SDL_RenderPresent(renderer);
}


int main() {
    srand(time(NULL));
    deck_init();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;

    SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    image = load_texture(renderer, "assets/kamo.png");

    //for (;;) {
        draw_screen();
    //}


    SDL_DestroyTexture (image);
    return 0;
}

