#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "../Scene.hh"
#include "../BulletManager.hh"

/**
 * A scene for putting all my test junk in so it's not cluttering up the main function.
 */
class TestScene: public Scene {
    BulletManager *bulletManager;
    sf::Font font;
    sf::Texture texture;
    sf::RectangleShape shape;
    sf::Text text;
    sf::RectangleShape background;
    sf::Shader shader;
    int i = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /**
     * Sets up the scene's junk.
     * @param bulletManager is the bullet manager which we shall use a little.
     */
    TestScene(BulletManager *bulletManager);

    void update(Transition *transition) override;
};

#endif
