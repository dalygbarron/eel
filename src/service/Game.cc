#include "scene/SplashScene.hh"
#include "scene/PlainScene.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include "service/Game.hh"

Game::Game(Engine const *engine) {
    this->engine = engine;
    // set up rendering window.
    int windowWidth = Utils::parseInt(engine->config->get("width"));
    int windowHeight = Utils::parseInt(engine->config->get("height"));
    this->window.create(
        sf::VideoMode(windowWidth, windowHeight),
        engine->config->get("title")
    );
    this->window.setVerticalSyncEnabled(true);
    this->view.setSize(windowWidth, windowHeight);
    this->view.setCenter(
        this->view.getSize().x / 2,
        this->view.getSize().y / 2
    );
    this->view = Utils::getLetterboxView(
        this->view,
        windowWidth,
        windowHeight
    );
    // set up first scene.
    char startFile[Constant::FILENAME_BUFFER_SIZE];
    engine->config->inRoot(startFile, engine->config->get("start"));
    this->scene = new SplashScene(engine);
}

int Game::run() {
    this->clock.restart();
    while (this->window.isOpen()) {
        this->update();
        this->clock.restart();
        if (!this->scene) break;
        this->render();
    }
    return 0;
}

unsigned char Game::handleEvents() {
    sf::Event event;
    unsigned char mouse = 0;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        } else if (event.type == sf::Event::Resized) {
            this->view = Utils::getLetterboxView(
                this->view,
                event.size.width,
                event.size.height
            );
        } else if (event.type == sf::Event::MouseButtonPressed) {
            mouse = 1;
        }
    }
    return mouse;
}

void Game::update() {
    unsigned char mouse = this->handleEvents();
    this->scene->update(this->clock.getElapsedTime().asSeconds(), mouse);
    this->transition(this->scene);
}

void Game::render() {
    this->window.setView(this->view);
    this->window.draw(*(this->scene));
    this->window.display();
}

void Game::transition(Scene *transitioning) {
    // TODO: this is likely not needed anymore, or at least it need not be like
    //       this anymore.
    if (!transitioning->transition[0]) return;
    spdlog::info("Transition '{}'", transitioning->transition);
    char operation = transitioning->transition[0];
    char type = transitioning->transition[1];
    Scene *newScene = 0;
    switch(type) {
        case 'p':
            newScene = new PlainScene(
                this->engine,
                transitioning->transition + 2
            );
            break;
        case 't':
            // TODO: this.
            break;
        case 's':
            // TODO: this.
            break;
        case 0:
            break;
        default:
            spdlog::error("No such scene letter code as '{}'", type);
            break;
    }
    if (operation == 'p') {
        if (!newScene) {
            spdlog::error("Trying to add nothing to stack.");
            throw -1;
        }
        if (this->scene) delete this->scene;
        this->scene = newScene;
    } else if (operation == 'r') {
        if (this->scene) delete this->scene;
        this->scene = 0;
        if (newScene) this->scene = newScene;
    } else {
        spdlog::error("Trying to perform unknown transtion '{}'", operation);
        delete newScene;
    }
}
