#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "scene/Scene.hh"
#include "model/BulletManager.hh"
#include "model/control/Panel.hh"

/**
 * A scene for putting all my test junk in so it's not cluttering up the main
 * function.
 */
class TestScene: public Scene {
    public:
        /**
         * Sets up the scene's junk.
         * @param engine contains the game services.
         */
        TestScene(Engine const *engine);

    private:
        BulletManager *bulletManager;
        sf::RectangleShape background;
        sf::Shader shader;
        Panel leftPanel;
        Panel rightPanel;

        virtual void render(
            sf::RenderTarget *target,
            sf::RenderStates states
        ) const override;

        virtual void logic(float delta) override;
};

#endif
