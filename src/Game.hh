#ifndef GAME_H
#define GAME_H

#include "BulletManager.hh"
#include "Listener.hh"
#include "Scene.hh"
#include <forward_list>

/**
 * Contains the main loop of the game, handles events, and creates and manages the game's scenes.
 */
class Game {
    /**
     * Behind the scenes datastructure for running timers. The idea is that a given time in the future (in ticks) is
     * registered along with a listener, and when that time is the current time they will be notified and removed.
     */
    class Timer {
    public:
        Listener *listener = 0;
        union {
            long time;
            Timer *next = 0;
        } content;
    };

    Config const *config;
    Repository *repository;
    BulletManager *bulletManager;
    std::forward_list<Scene *> scenes;
    sf::RenderWindow window;
    sf::View view;
    int tick;
    Timer timers[Constant::TIMER_LIMIT];
    Timer *emptyTimer;

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
     * Does the frame by frame transition of scenes (or does nothing most of the time).
     * @param transition is the object defining how the current scene stack should be updated.
     */
    void transition();

public:
    /**
     * Builds the thing and gets it's dependencies injected.
     * @param config        is the game's configuration.
     * @param repository    is where the game will get it's assets.
     * @param bulletManager is used by some scenes for their enjoyment.
     */
    Game(Config const *config, Repository *repository, BulletManager *bulletManager);

    /**
     * Runs the game.
     * @return 0 if it's all been good, and another value if there was an unhandled exception in the game logic.
     */
    int run();

    /**
     * Starts a timer which will send a signal when done.
     * @param listener is the listener to inform when it is done.
     * @param time     is the number of ticks from now at which the timer is done.
     */
    void startTimer(Listener *listener, long time);
};

#endif
