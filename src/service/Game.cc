#include "scene/SplashScene.hh"
#include "scene/PlainScene.hh"
#include "scene/WalkScene.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include "service/Game.hh"

Game::Game(Engine const &engine):
    engine(engine)
{
    this->window.create(
        sf::VideoMode(engine.config.dimensions.x, engine.config.dimensions.y),
        engine.config.name
    );
    this->window.setVerticalSyncEnabled(true);
    this->view.setSize(engine.config.dimensions);
    this->view.setCenter(
        this->view.getSize().x / 2,
        this->view.getSize().y / 2
    );
    this->view = Utils::getLetterboxView(this->view, sf::Vector2i(
        engine.config.dimensions.x,
        engine.config.dimensions.y
    ));
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
                sf::Vector2i(event.size.width, event.size.height)
            );
        } else if (event.type == sf::Event::MouseButtonPressed) {
            mouse = 1;
        }
    }
    return mouse;
}

void Game::update() {
    unsigned char mouse = this->handleEvents();
    this->scene->update(
        this->clock.getElapsedTime().asSeconds(),
        mouse,
        this->view
    );
    this->transition(*this->scene);
}

void Game::render() {
    this->window.setView(this->view);
    this->window.draw(*this->scene);
    this->window.display();
}

void Game::transition(Scene &transitioning) {
    // TODO: this is dumb as hell can we please for the love of god make
    //       something better bloody hell man.
    if (!transitioning.transition[0]) return;
    spdlog::info("Transition '{}'", transitioning.transition);
    char operation = transitioning.transition[0];
    char type = transitioning.transition[1];
    Scene *newScene = 0;
    switch(type) {
        case 'p': {
            newScene = new PlainScene(
                this->engine,
                transitioning.transition[2]
            );
        }
        break;
        case 'w': {
            Repository<WalkStage> const &walkStageRepo =
                this->engine.getWalkStageRepository();
            newScene = new WalkScene(
                this->engine,
                walkStageRepo.get(transitioning.transition[2]).get()
            );
        }
        break;
        case 0: break;
        default: {
            spdlog::error("No such scene letter code as '{}'", type);
        }
        break;
    }
    if (operation == 'p') {
        if (this->scene) delete this->scene;
        if (newScene) this->scene = newScene;
        else spdlog::error("Trying to add nothing to stack.");
    } else if (operation == 'r') {
        if (this->scene) delete this->scene;
        this->scene = 0;
        if (newScene) this->scene = newScene;
    } else {
        spdlog::error("Trying to perform unknown transtion '{}'", operation);
        delete newScene;
    }
}
