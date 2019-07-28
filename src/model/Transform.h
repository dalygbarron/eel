#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "src/model/Vector.h"

/**
 * Represents a transformation in 3d space.
 */
struct Transform {
    /** a position of movement from the origin */
    struct Vector pos;

    /** size relative to the original size in both dimensions */
    struct Vector scale;

    /** the spinning from right way up in radians */
    float rotation;
};

#endif
