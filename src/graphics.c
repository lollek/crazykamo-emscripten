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

void highlight_card(Card *card) {
    if (card == NULL) {
        return;
    }

    int x_start = (card->position % 3) * CARD_SIZE;
    int y_start = (card->position / 3) * CARD_SIZE;

    int const num_points = 5;
    SDL_Point const points[num_points] = {
        {x_start, y_start},
        {x_start + CARD_SIZE -1, y_start},
        {x_start + CARD_SIZE -1, y_start + CARD_SIZE -1},
        {x_start, y_start + CARD_SIZE -1},
        {x_start, y_start},
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(renderer, points, num_points);
}

void gfx_init() {
    SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    image = load_texture(renderer, "assets/kamo.png");
}

void gfx_exit() {
    SDL_DestroyTexture(image);
}

void gfx_draw_screen(Card *highlighted_card) {
    SDL_RenderClear(renderer);

    for (int i = 0; i < NUM_CARDS; ++i) {
        Card *card = deck_get_card_by_position(i);
        SDL_Rect const src = {
            .x = (card->id % CARDS_PER_ROW) * CARD_SIZE,
            .y = (card->id / CARDS_PER_ROW) * CARD_SIZE,
            .w = CARD_SIZE,
            .h = CARD_SIZE,
        };
        SDL_Rect const dst = {
            .x = (card->position % CARDS_PER_ROW) * CARD_SIZE,
            .y = (card->position / CARDS_PER_ROW) * CARD_SIZE,
            .w = CARD_SIZE,
            .h = CARD_SIZE,
        };
        double const angle = 90 * card->rotation;
        SDL_RenderCopyEx(renderer, image, &src, &dst, angle, NULL, SDL_FLIP_NONE);
    }

    highlight_card(highlighted_card);

    SDL_RenderPresent(renderer);
}

