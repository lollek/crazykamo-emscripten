#ifndef CARD_H
#define CARD_H

typedef struct Card {
    /*
     * Position on kamo.png [0..8], like this:
     * 0 1 2
     * 3 4 5
     * 6 7 8
     */
    int id;

    /* Position on the screen [0..8], like this:
     * 0 1 2
     * 3 4 5
     * 6 7 8 */
    int position;

    // Rotation of card [0..3]
    int rotation;
} Card;

#endif /* CARD_H */
