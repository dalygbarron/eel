#ifndef SPLASH_SCENE_H
#define SPLASH_SCENE_H

#include "../Scene.hh"

/**
 * First scene when game starts, and last when it finishes.
 */
class SplashScene: public Scene {
    static unsigned char const LOGO[];
    static unsigned int const LOGO_SIZE;
    sf::Texture texture;
    sf::RectangleShape shape;
    float width;
    float height;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic() override;

public:
    /**
     * Does setting up.
     */
    SplashScene(Builder const *builder, Timer *timer, Config const *config);

};

#endif
