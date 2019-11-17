#ifndef GAME_H
#define GAME_H

#include "scene/Scene.hh"
#include <forward_list>

/**
 * Contains the main loop of the game, handles events, and creates and manages
 * the game's scenes. Also keeps track of time.  */
class Game {
    public:
        /**
         * Builds the thing and gets it's dependencies injected.
         * @param engine contains the game services.
         */
        Game(Engine const &engine);

        /**
         * Runs the game.
         * @return 0 if it's all been good, and another value if there was an
         *         unhandled exception in the game logic.
         */
        int run();

    private:
        Engine const &engine;
        Scene *scene;
        sf::RenderWindow window;
        sf::View view;
        sf::Clock clock;
        sf::Clock fps;
        int i;

        /**
         * Gets the game to handle events.
         */
        unsigned char handleEvents();

        /**
         * Updates the game's state.
         */
        void update();

        /**
         * Renders the game.
         */
        void render();

        /**
         * Checks if the scene should be transitioned and does the stuff if so.
         * TODO: update this to not use these weird strings.
         * @param transitioning is the scene that may or may not be
         *        transitioned out of.
         */
        void transition(Scene &transitioning);
};

#endif
