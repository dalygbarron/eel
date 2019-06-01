#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "../Scene.hh"

/**
 * A scene for putting all my test junk in so it's not cluttering up the main function.
 */
class TestScene: public Scene {
    sf::Font font;
    sf::Texture texture;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    TestScene();

    void update(Transition *transition) override;

};

#endif
