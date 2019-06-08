#include <iostream>
#include <fstream>
#include <forward_list>
#include <SFML/Graphics.hpp>

// TODO: find a better spot for this.
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/daily_file_sink.h"
#include "BulletManager.hh"
#include "scenes/TestScene.hh"

#define WIDTH 512
#define HEIGHT 256

/**
 * The main loop of the game.
 */
void run(char const *gameFile) {
    Repository repository;
    Game game(&repository, gameFile);
    BulletManager bulletManager(&game, &repository);

    std::forward_list<Scene *> scenes;
    scenes.push_front(new TestScene(&bulletManager));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "World of Piss");
    window.setFramerateLimit(60);
    // Main loop of game.
    int i = 0;
    Transition transition;
    while (window.isOpen()) {
        // Event handling.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        // Updating current scene.
        scenes.front()->update(&transition);
        // Rendering.
        window.clear();
        window.draw(*(scenes.front()));
        window.display();
        // Scene transition.
        if (transition.action == Transition::POP) {
            scenes.pop_front();
        } else if (transition.action == Transition::PUSH) {
            scenes.push_front(transition.scene);
        } else if (transition.action == Transition::REPLACE) {
            scenes.pop_front();
            scenes.push_front(transition.scene);
        }
        // Timekeeping.
        i++;
        if (!(i % 300)) spdlog::info("tickx300");
    }
}

/**
 * Start of the program.
 * @param argc is the number of commandline arguments given.
 * @param argv is an array of commandline arguments as pointers to strings.
 * @return 0 when program exits expectedly, and otherwise returns something else probably meaningless.
 */
int main(int argc, char **argv) {
    // Start logging right away.
    spdlog::set_default_logger(spdlog::daily_logger_mt("heart", "logs/log.log", 2, 30));
    spdlog::flush_every(std::chrono::seconds(5));
    spdlog::info("Game Commencing Normally");
    // run main loop in try/catch.
    try {
        // TODO: allow you to set the file via commandline args.
        run("example/game.ini");
    } catch (int i) {
        spdlog::critical("Uncaught error '{}', goodbye", i);
        return 1;
    }
    // all over.
    spdlog::info("Game Ending Normally");
    return 0;
}
