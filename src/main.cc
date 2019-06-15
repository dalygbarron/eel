#include <iostream>
#include <fstream>
#include <forward_list>
#include <SFML/Graphics.hpp>

// TODO: find a better spot for this.
//#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/daily_file_sink.h"
#include "BulletManager.hh"
#include "scenes/TestScene.hh"

#define WIDTH 1280
#define HEIGHT 960

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    bool horizontalSpacing = true;
    if (windowRatio < viewRatio) horizontalSpacing = false;
    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    return view;
}

/**
 * The main loop of the game.
 */
void run(char const *gameFile) {
    Game game(gameFile);
    Repository repository(&game);
    BulletManager bulletManager(&game, &repository);

    std::forward_list<Scene *> scenes;
    scenes.push_front(new TestScene(&bulletManager));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), game.get("title"));
    sf::View view;
    view.setSize(WIDTH, HEIGHT);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view = getLetterboxView(view, WIDTH, HEIGHT);
    window.setFramerateLimit(FPS);
    // Main loop of game.
    sf::Clock clock;
    int i = 0;
    Transition transition;
    while (window.isOpen()) {
        // Event handling.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::Resized) view = getLetterboxView(view, event.size.width, event.size.height);
        }
        // Updating current scene.
        scenes.front()->update(&transition);
        // Rendering.
        window.setView(view);
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
        if (!(i % 300)) {
            float fps = 300.0 / clock.getElapsedTime().asSeconds();
            if (fps < FPS_WARN) spdlog::warn("FPS: {}", fps);
            else spdlog::debug("FPS: {}", fps);
            clock.restart();
        }
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
    spdlog::set_default_logger(spdlog::daily_logger_mt("heart", "logs/piss2.log", 2, 30));
    spdlog::flush_on(spdlog::level::debug); // TODO: obviously change this for production to error.
    spdlog::flush_every(std::chrono::seconds(10));
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
