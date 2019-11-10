#ifndef MOB_H
#define MOB_H

#include <SFML/Graphics.hpp>

/**
 * Represents a thing that can exist in three dimensional space and can be
 * stuffed into a big vertex buffer to all be rendered together sorted.
 */
class Mob {
    public:
        int dirty = false;
        int alive = false;
        sf::Vector3f position;
        float index = 0;
        Pane *pane;
};

#endif
