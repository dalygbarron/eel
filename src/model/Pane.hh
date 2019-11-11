#ifndef PANE_H
#define PANE_H

#include "model/RatPack.hh"
#include <SFML/Graphics.hpp>

/**
 * Represents four vertices and their transformation and shiet. It assumes the
 * vertices are set whenever it is used so that is why the default constructor
 * is private for friends only.
 */
class Pane {
    public:
        float order;

        /**
         * make a whole sprite hell yeah man. Also it makes it centred.
         * TODO: I know this is not entirely relevant but you may be frightened
         *       by the fact that all of these form methods take a string. well
         *       don't be because what we are going to do is we are going to
         *       have an animation object which gets the size from the rat pack
         *       but then it does all the animationy shit straight on the
         *       vertices in the pane hell yeah man.
         * @param ratPack is the ratpack with which we will find the rat.
         * @param rat     is the name of the rat in the pack we want.
         */
        void form(RatPack const &ratPack, char const &rat);

        /**
         * Sets the pane's position. Each vertex will be positioned relatively
         * around the new pos as it was originally around the (0, 0) point.
         * @param pos is the new position.
         */
        void setPosition(sf::Vector2f pos);

        /**
         * Adds an amount to the pane's current position.
         * @param delta is the amount to add.
         */
        void addPosition(sf::Vector2f delta);

        /**
         * Moves the pane's content without moving it's origin.
         * @param delta is the amount in each axis to move the content.
         */
        void shift(sf::Vector2f delta);

        /**
         * Sets the pane's vertices to the given rectangle without changing
         * it's current position.
         * @param shape is the shape it's vertices should now have.
         * @param image is the texture mapping it should now have.
         */
        void set(sf::FloatRect shape, sf::FloatRect image);

        /**
         * Get rid of this rubbish.
         */
        void hide();

    private:
        friend class PaneBuffer;
        friend class RatPack;

        /**
         * Default constructor is private because pane should always have
         * vertices so it can only be created without vertices when we can
         * trust that the creator will give them vertices.
         */
        Pane();

        sf::Vertex *vertices;
        sf::Vector2f position;
        int dirty;
};

#endif
