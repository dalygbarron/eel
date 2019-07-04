#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "../Scene.hh"
#include "../BulletManager.hh"
#include "../controls/Panel.hh"

/**
 * A scene for putting all my test junk in so it's not cluttering up the main function.
 */
class TestScene: public Scene {
    BulletManager *bulletManager;
    Config const *config;
    sf::RectangleShape background;
    sf::Shader shader;
    Panel leftPanel;
    Panel rightPanel;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic(long tick) override;

public:
    /**
     * Sets up the scene's junk.
     * @param builder       is the gui builder.
     * @param timer         is the timer.
     * @param bulletManager is the bullet manager which we shall use a little.
     * @param repository    allows the scene access to the game assets.
     */
    TestScene(Builder const *builder, Timer *timer, BulletManager *bulletManager, Config const *config, Repository *repository);
};

#endif
