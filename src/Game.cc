#include "Game.hh"
#include "Utils.hh"

void Game::handleEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        } else if (event.type == sf::Event::Resized) {
            this->view = Utils::getLetterboxView(this->view, event.size.width, event.size.height);
        }
    }
}

void Game::update(Transition *t) {
    scenes.front()->update(t);
}

void Game::render() {
    this->window.setView(this->view);
    this->window.clear();
    this->window.draw(*(scenes.front()));
    this->window.display();
}

void Game::transition(Transition *t) {
    if (t->action == Transition::POP) {
        scenes.pop_front();
    } else if (t->action == Transition::PUSH) {
        scenes.push_front(t->scene);
    } else if (t->action == Transition::REPLACE) {
        scenes.pop_front();
        scenes.push_front(t->scene);
    }
}

Game::Game(Config const *config, Repository *repository) {
    this->config = config;
    this->repository = repository;
    // set up rendering window.
    int windowWidth = config->get("width");
    int windowHeight = config->get("height");
    this->window.create(sf::VideoMode(windowWidth, windowHeight), config->get("title"));
    this->window.setFramerateLimit(Config::FPS);
    this->view.setSize(windowWidth, windowHeight);
    this->view.setCenter(this->view.getSize().x / 2, this->view.getSize().y / 2);
    this->view = Utils::getLetterboxView(this->view, windowWidth, windowHeight);
    // set up a test scene.
    this->scenes.push_front(new TestScene(&bulletManager));
}

int Game::run() {
    // Main loop of game.
    sf::Clock clock;
    int i = 0;
    Transition t;
    while (this->window.isOpen()) {
        this->handleEvents();
        this->update(&t);
        this->render();
        this->transition(&t);
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
