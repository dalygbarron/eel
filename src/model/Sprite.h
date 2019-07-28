#ifndef SPRITE_H
#define SPRITE_H

#include "Vertex.h"
#include "Transform.h"
#include "Vector.h"

/**
 * Represents four vertices with a texture on them in a vertex array.
 * They are always centered on their position because it will make the rotation
 * calculations quicker I think.
 */
struct Sprite {
    struct Vector radii;

    /** Stores the sprite's translation from it's origin */
    struct Transform transform;

    /** The vertices of the sprite */
    // TODO: should be opengl vertices.
    struct Vertex *vertices;
};

#endif
