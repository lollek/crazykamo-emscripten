#ifndef GRAPHICS_H
#define GRAPHICS_H

#define CARD_SIZE 150
#define CANVAS_WIDTH (CARD_SIZE * CARDS_PER_ROW)
#define CANVAS_HEIGHT (CARD_SIZE * CARDS_PER_ROW)


void gfx_init();
void gfx_exit();
void gfx_draw_screen();

#endif /* GRAPHICS_H */
