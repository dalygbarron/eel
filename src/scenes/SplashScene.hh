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
    char const *startScript;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic(long tick) override;

public:
    // TODO: make this short in debug mode and long in main mode.
    constexpr static int const WAIT = 90;

    /**
     * Does setting up.
     * @param config  is the game configuration.
     * @param builder is the gui builder thingo.
     * @param timer   is the time keeper thingy.
     * @param radio   is the music plauer.
     */
    SplashScene(Config const *config, Builder const *builder, Timer *timer, Radio *radio);
};

#endif
