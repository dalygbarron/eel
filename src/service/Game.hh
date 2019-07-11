#ifndef GAME_H
#define GAME_H

#include "model/scene/Scene.hh"
#include "interface/Listener.hh"
#include "service/Timer.hh"
#include <forward_list>

/**
 * Contains the main loop of the game, handles events, and creates and manages the game's scenes.
 */
class Game {
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
    Config const *config;
    ControlBuilder const *controlBuilder;
    Repository *repository;
    Timer *timer;
    Radio *radio;

    /**
     * Builds the thing and gets it's dependencies injected.
     * @param config         is the game's configuration.
     * @param repository     is where the game will get it's assets.
     * @param controlBuilder is the gui builder.
     * @param timer          is used to time stuff.
     * @param radio          is the game's music player.
     */
    Game(
        Config const *config,
        Repository *repository,
        ControlBuilder const *controlBuilder,
        Timer *timer,
        Radio *radio
    );

    /**
     * Runs the game.
     * @return 0 if it's all been good, and another value if there was an unhandled exception in the game logic.
     */
    int run();
};

#endif
