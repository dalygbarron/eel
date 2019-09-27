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

        /**
         * Move the mob's vertices to the given location.
         * @param index is the exact place to write to.
         */
        void moveTo(sf::Vertex *index) const;

        /**
         * Tells you if this mob should be rendered behind another.
         * @param other is the other mob to compare against.
         * @return true if this should be behind, false for equal or in front.
         */
        int behind(Mob const *other) const;

        /**
         * Sorts a list of mobs and tells you what range of items was changed
         * by the sorting.
         * @param mobs is a pointer to an array of pointers to mobs.
         * @param n    is the number of mobs in the array.
         * @return a vector where x is the first edited index and y is the last
         *         edited index.
         */
        static sf::Vector2u sort(Mob const **mobs, int n);

    private:
        sf::Vertex *vertices;
};

#endif
