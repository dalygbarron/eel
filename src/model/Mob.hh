#ifndef MOB_H
#define MOB_H

#include "model/Pane.hh"
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

        /**
         * Sets the mob's pane to use.
         * @param pane is the pane to use.
         */
        void attach(Pane *pane);

        /**
         * Places the mob in 3d space and updates the z index on it's pane and
         * it's location on the screen accordingly.
         * @param pos is the new position.
         */
        void place(sf::Vector3f pos);
};

#endif
