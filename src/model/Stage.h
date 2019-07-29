#ifndef STAGE_H
#define STAGE_H

/**
 * Set of stuff to render.
 */
struct Stage {
    /** vertices of the sprites in the stage. should be kept contiguous */
    struct Vertex *sprites;

    /** current number of sprites in the stage */
    int nSprites;

    /** maximum number of sprites in the stage */
    int maxSprites;

    /** Tiles in the stage. should be kept contiguous */
    struct Vertex *tiles;

    /** current number of tiles in stage */
    int nTiles;

    /** maximum number of tiles in stage */
    int maxTiles;

    /** stage's background colour as an int */
    int bg;

    // TODO: add a shader program for the background.
    //       it will be passed the time in ticks and the background colour and
    //       maybe some other stuff that I think of.
};

#endif
