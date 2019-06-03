#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "../Scene.hh"

/**
 * A scene for putting all my test junk in so it's not cluttering up the main function.
 */
class TestScene: public Scene {
    sf::Font font;
    sf::Texture texture;
    sf::RectangleShape shape;
    sf::Text text;
    sf::RectangleShape background;
    sf::Shader shader;
    BulletManager *bullets;
    int i = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /**
     * Sets up the scene's junk.
     */
    TestScene();

    void update(Transition *transition) override;
};

#endif
