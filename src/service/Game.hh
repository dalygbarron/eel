#ifndef GAME_H
#define GAME_H

#include "scene/Scene.hh"
#include "interface/Listener.hh"
#include "service/Timer.hh"
#include <forward_list>

/**
 * Contains the main loop of the game, handles events, and creates and manages the game's scenes.
 */
class Game {
    Engine const *engine;
    std::forward_list<Scene *> scenes;
    sf::RenderWindow window;
    sf::View view;

    /**
     * Gets the game to handle events.
     */
    void handleEvents();

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
     * @param transitioning is the scene that may or may not be transitioned out of.
     */
    void transition(Scene *transitioning);

public:
    /**
     * Builds the thing and gets it's dependencies injected.
     * @param engine contains the game services.
     */
    Game(Engine const *engine);

    /**
     * Runs the game.
     * @return 0 if it's all been good, and another value if there was an unhandled exception in the game logic.
     */
    int run();
};

#endif
