#include "Game.hh"
#include "Constant.hh"
#include "Utils.hh"
#include "scenes/PlainScene.hh"
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
    // update timers.
    for (int i = 0; i < Constant::TIMER_LIMIT; i++) {
        if (this->timers[i].listener && this->timers[i].content.time == this->tick) {
            this->timers[i].listener->listen(Signal(Signal::TYPE_TIMED));
            this->timers[i].listener = 0;
            this->timers[i].content.next = this->emptyTimer;
            this->emptyTimer = this->timers + i;
        }
    }
    // update scene.
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
    for (int i = 0; i < Constant::TIMER_LIMIT - 1; i++) {
        this->timers[i].listener = 0;
        this->timers[i].content.next = this->timers + i + 1;
    }
    this->timers[Constant::TIMER_LIMIT - 1].listener = 0;
    this->timers[Constant::TIMER_LIMIT - 1].content.next = 0;
    this->emptyTimer = this->timers;
    // set up first scene.
    char startFile[Constant::FILENAME_BUFFER_SIZE];
    config->inRoot(startFile, config->get("start"));
    this->scenes.push_front(new PlainScene(repository, startFile));
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

void Game::startTimer(Listener *listener, long time) {
    if (!this->emptyTimer) {
        spdlog::error("Trying to start timer but all are in use");
    } else {
        Timer *next = this->emptyTimer->content.next;
        this->emptyTimer->listener = listener;
        this->emptyTimer->content.time = this->tick + time;
        this->emptyTimer = next;
    }
}
