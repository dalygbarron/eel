#include "Game.hh"
#include "Constant.hh"
#include "Utils.hh"
#include "scenes/SplashScene.hh"
#include "scenes/PlainScene.hh"
#include "scenes/TestScene.hh"
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
    this->timer->update();
    char transitionBuffer[Constant::FILENAME_BUFFER_SIZE];
    transitionBuffer[0] = 0;
    scenes.front()->update(this->timer->getTick(), transitionBuffer);
    if (transitionBuffer[0]) this->transition(transitionBuffer);
}

void Game::render() {
    this->window.setView(this->view);
    this->window.draw(*(scenes.front()));
    this->window.display();
}

void Game::transition(char const *transitionBuffer) {
    spdlog::info("Transition '{}'", transitionBuffer);
    char operation = transitionBuffer[0];
    char type = transitionBuffer[1];
    Scene *scene = 0;
    switch(type) {
        case 'p':
            scene = new PlainScene(this->builder, this->timer, this->repository, transitionBuffer + 2);
            break;
        case 't':
            // TODO: this.
            scene = 0;
            break;
        case 's':
            // TODO: this.
            scene = 0;
            break;
        case 0:
            break;
        default:
            spdlog::error("No such scene letter code as '{}'", type);
            break;
    }
    if (operation == 'p') {
        if (!scene) {
            spdlog::error("Trying to add nothing to stack.");
            throw -1;
        }
        this->scenes.push_front(scene);
    } else if (operation == 'r') {
        this->scenes.pop_front();
        if (scene) this->scenes.push_front(scene);
    } else {
        spdlog::error("Trying to perform unknown transtion '{}'", operation);
        delete scene;
    }
}

Game::Game(
    Config const *config,
    Repository *repository,
    Builder const *builder,
    Timer *timer,
    BulletManager *bulletManager
) {
    this->config = config;
    this->repository = repository;
    this->builder = builder;
    this->timer = timer;
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

    // set up first scene.
    char startFile[Constant::FILENAME_BUFFER_SIZE];
    config->inRoot(startFile, config->get("start"));
    this->scenes.push_front(new SplashScene(builder, timer, config));
    //this->scenes.push_front(new PlainScene(builder, timer, repository, startFile));
    //this->scenes.push_front(new TestScene(bulletManager, config, repository));
}

int Game::run() {
    // Main loop of game.
    while (this->window.isOpen()) {
        this->handleEvents();
        this->update();
        this->render();
    }
    return 0;
}
