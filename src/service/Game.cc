#include "scene/SplashScene.hh"
#include "scene/PlainScene.hh"
#include "scene/TestScene.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include "service/Game.hh"

void Game::handleEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        } else if (event.type == sf::Event::Resized) {
            this->view = Utils::getLetterboxView(
                this->view,
                event.size.width,
                event.size.height
            );
        } else {
            scenes.front()->onEvent(&event);
        }
    }
}

void Game::update() {
    this->engine->timer->update();
    Scene *scene = this->scenes.front();
    scene->update(this->engine->timer->getTick());
    this->transition(scene);
}

void Game::render() {
    this->window.setView(this->view);
    this->window.draw(*(scenes.front()));
    this->window.display();
}

void Game::transition(Scene *transitioning) {
    // TODO: this is likely not needed anymore, or at least it need not be like
    //       this anymore.
    if (!transitioning->transition[0]) return;
    spdlog::info("Transition '{}'", transitioning->transition);
    char operation = transitioning->transition[0];
    char type = transitioning->transition[1];
    Scene *scene = 0;
    switch(type) {
        case 'p':
            scene = new PlainScene(
                this->engine,
                transitioning->transition + 2
            );
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
    transitioning->transition[0] = 0;
}

Game::Game(Engine const *engine) {
    this->engine = engine;
    // set up rendering window.
    int windowWidth = Utils::parseInt(engine->config->get("width"));
    int windowHeight = Utils::parseInt(engine->config->get("height"));
    this->window.create(
        sf::VideoMode(windowWidth, windowHeight),
        engine->config->get("title")
    );
    this->window.setFramerateLimit(Constant::FPS);
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
    this->scenes.push_front(new SplashScene(engine));
}

int Game::run() {
    // Main loop of game.
    while (this->window.isOpen()) {
        this->handleEvents();
        this->update();
        if (this->scenes.empty()) break;
        this->render();
    }
    return 0;
}
