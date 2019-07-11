#ifndef GAME_H
#define GAME_H

#include "BulletManager.hh"
#include "Listener.hh"
#include "Timer.hh"
#include "Scene.hh"
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
    Config const * const config;
    Repository * const repository;
    Builder const * const builder;
    Timer * const timer;
    Radio * const radio;
    BulletManager * const bulletManager;

    /**
     * Builds the thing and gets it's dependencies injected.
     * @param config        is the game's configuration.
     * @param repository    is where the game will get it's assets.
     * @param builder       is the gui builder.
     * @param timer         is used to time stuff.
     * @param radio         is the game's music player.
     * @param bulletManager is used by some scenes for their enjoyment.
     */
    Game(
        Config const *config,
        Repository *repository,
        Builder const *builder,
        Timer *timer,
        Radio *radio,
        BulletManager *bulletManager
    );

    /**
     * Runs the game.
     * @return 0 if it's all been good, and another value if there was an unhandled exception in the game logic.
     */
    int run();
};

#endif
