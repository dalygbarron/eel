#ifndef PLAIN_SCENE_H
#define PLAIN_SCENE_H

#include "model/scene/Scene.hh"
#include "model/Script.hh"
#include "service/Repository.hh"

/**
 * A scene where there is nothing but a background image and a script is run.
 */
class PlainScene: public Scene {
    Script *script;
    char *file;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic(long tick) override;

public:
    /**
     * Creates the plain scene.
     * @param engine   contains the game services.
     * @param filename is the name of the script file to run.
     */
    PlainScene(Engine const *engine, char const *filename);
};

#endif
