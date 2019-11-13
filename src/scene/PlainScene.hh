#ifndef PLAIN_SCENE_H
#define PLAIN_SCENE_H

#include "scene/Scene.hh"
#include "model/Script.hh"

/**
 * A scene where there is nothing but a background image and a script is run.
 */
class PlainScene: public Scene {
    public:
        /**
         * Creates the plain scene.
         * @param engine   contains the game services.
         * @param filename is the name of the script file to run.
         */
        PlainScene(Engine const &engine, char const &filename);

        /**
         * Deletes the plain scene.
         */
        virtual ~PlainScene();

    private:
        Script script;

        virtual void logic(float delta, sf::View &view) override;
};

#endif
