#ifndef RAT_H
#define RAT_H

/**
 * Wraps around a set of four vertices that exist in some set of vertices and
 * lets you manipulate them as if they are a sprite.
 * Note that rotation and scaling are not implemented. Hypothetically they
 * could be implemented but I don't want to use them so I am not going to.
 */
class Rat {
    public:
        /**
         * Creates the rat with a set of vertices which should be already set
         * in their original position without transform.
         * @param vertices is a pointer to the first of it's four vertices.
         */
        Rat(sf::Vertex *vertices);

        /**
         * Gives the rat's current offset from it's original location.
         * @return the position.
         */
        sf::Vector2f getPosition();

        /**
         * Sets the rat's offset from it's original position.
         * @param position is the location to set it to.
         */
        void setPosition(sf::Vector2f position);

        /**
         * Adds to the position of each of the rat's vertices.
         * @param delta is the amount to add in 2d.
         */
        void addPosition(sf::Vector2f delta);

    private:
        sf::Vertex *vertices;
        sf::Vector2f position;
};

#endif
