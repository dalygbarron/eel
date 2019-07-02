#ifndef SPLASH_SCENE_H
#define SPLASH_SCENE_H

#include "../Scene.hh"

/**
 * First scene when game starts, and last when it finishes.
 */
class SplashScene: public Scene {
    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic() override;

public:
    
    SplashScene();

};

#endif
