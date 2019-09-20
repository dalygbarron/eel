#ifndef MOB_H
#define MOB_H

/**
 * Represents a thing that can exist in three dimensional space and can be
 * stuffed into a big vertex buffer to all be rendered together sorted.
 */
class Mob {
    public:
        int dirty = false;
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
        int behind(Mob *other) const;

    private:
        sf::Vertex *vertices;
};

#endif
