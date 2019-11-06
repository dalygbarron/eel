#ifndef PANE_H
#define PANE_H

/**
 * Represents four vertices and their transformation and shiet.
 * One day we could add scaling and rotating but it's not relevant to this
 * game so far so who cares.
 */
class Pane {
    public:
        /**
         * Sets the pane's position. Each vertex will be positioned relatively
         * around the new pos as it was originally around the (0, 0) point.
         * @param pos is the new position.
         */
        void setPosition(sf::Vector2i pos);

        /**
         * Adds an amount to the pane's current position.
         * @param delta is the amount to add.
         */
        void addPosition(sf::Vector2i delta);

    private:
        friend class PaneBuffer;
        friend class RatPack;

        sf::Vertex *topLeft;
        sf::Vertex *topRight;
        sf::Vertex *bottomRight;
        sf::Vertex *bottomLeft;
        sf::Vector2i position;
}

#endif
