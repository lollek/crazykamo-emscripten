#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "deck.h"

#include "graphics.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* image;

static SDL_Texture* load_texture(SDL_Renderer* renderer, char const* const path) {
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

void gfx_init() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    image = load_texture(renderer, "assets/kamo.png");
}

void gfx_exit() {
    SDL_DestroyTexture(image);
}

void gfx_draw_screen() {
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
