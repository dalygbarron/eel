#ifndef SPRITE_ARRAY_H
#define SPRITE_ARRAY_H

/**
 * Contains a bunch of vertices. 
 */
struct SpriteArray {
    int n;
    int max;
    struct Vertex *vertices;
};

#endif
