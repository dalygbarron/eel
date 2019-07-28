#ifndef SPRITE_ARRAY_H
#define SPRITE_ARRAY_H

/**
 * A whole array of sprite vertices to be rendered at the same time.
 */
struct SpriteArray {
    /** Maximum number of sprites that can be held */
    int max;

    /** Current number of sprites */
    int n;

    /** the actual sprite vertices */
    struct Vertex *vertices;

    /** The texture sheet to render the sprites with
     * TODO: figure out what this is */
};

#endif
