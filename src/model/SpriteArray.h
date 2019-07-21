#ifndef SPRITE_ARRAY_H
#define SPRITE_ARRAY_H

#include "model/Node.h"

/**
 * Wraps around an SFML vertex array to keep a free list of quads that are in use and those that are not.
 */
struct SpriteArray {
    // The SFML vertice array that renders onto the GPU.
    struct sfVertexArray vertices;
    
    // The texture that the sprites should be rendered with.
    struct sfTexture *texture = 0;

    // Linked list of free quads.
    struct Node *free = 0;
};

#endif
