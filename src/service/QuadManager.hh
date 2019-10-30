#ifndef QUAD_MANAGER_H
#define QUAD_MANAGER_H

/**
 * Manages quads.
 */
class QuadManager {
    public:
        /**
         * Creates the quad manager and gives it it's needed stuff.
         * @param texture is the texture the quads are drawn with.
         * @param max     is the maximum number of quads.
         */
        QuadManager(sf::Texture const *texture, int max);

        ~QuadManager();

    private:

};

#endif
