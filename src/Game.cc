#include "Game.hh"
#include "Constant.hh"
#include "Utils.hh"
#include "spdlog/spdlog.h"

void Game::handleEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        } else if (event.type == sf::Event::Resized) {
            this->view = Utils::getLetterboxView(this->view, event.size.width, event.size.height);
        } else {
            scenes.front()->onEvent(&event);
        }
    }
}

void Game::update() {
    scenes.front()->update();
}

void Game::render() {
    this->window.setView(this->view);
    this->window.clear();
    this->window.draw(*(scenes.front()));
    this->window.display();
}

Game::Game(Config const *config, Repository *repository, BulletManager *bulletManager) {
    this->config = config;
    this->repository = repository;
    this->bulletManager = bulletManager;
    // set up rendering window.
    int windowWidth = Utils::parseInt(config->get("width"));
    int windowHeight = Utils::parseInt(config->get("height"));
    this->window.create(sf::VideoMode(windowWidth, windowHeight), config->get("title"));
    this->window.setFramerateLimit(Constant::FPS);
    this->view.setSize(windowWidth, windowHeight);
    this->view.setCenter(this->view.getSize().x / 2, this->view.getSize().y / 2);
    this->view = Utils::getLetterboxView(this->view, windowWidth, windowHeight);
    // Set up the timers.
    this->tick = 0;

    // set up a test scene.
    this->scenes.push_front(new TestScene(bulletManager, config, repository));
}

int Game::run() {
    // Main loop of game.
    sf::Clock clock;
    while (this->window.isOpen()) {
        this->handleEvents();
        this->update();
        this->render();
        // Timekeeping.
        this->tick++;
        if (!(this->tick % 300)) {
            float fps = 300.0 / clock.getElapsedTime().asSeconds();
            if (fps < Constant::FPS_WARN) spdlog::warn("FPS: {}", fps);
            else spdlog::debug("FPS: {}", fps);
            clock.restart();
        }
    }
    return 0;
}

void Game::addTimer(Listener *listener, long time) {
    if (!this->emptyTimer) {
        spdlog::error("Trying to start timer but all are in use");
    } else {
        Timer *next = this->emptyTimer->content.next;
        this->emptyTime->listener = listener;
        this->emptyTime->content.time = this->tick + time;
    }
}
