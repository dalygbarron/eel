#ifndef PLAIN_SCENE_H
#define PLAIN_SCENE_H

#include "../Scene.hh"
#include "../Script.hh"
#include "../Repository.hh"

/**
 * A scene where there is nothing but a background image and a script is run.
 */
class PlainScene: public Scene {
    Repository *repository;
    Script *script;
    char *file;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic(long tick) override;

public:
    /**
     * Creates the plain scene.
     * @param config     is the game configuration.
     * @param builder    is the gui builder.
     * @param timer      is the timer.
     * @param repository is the game asset repository.
     * @param script     is the filename of the script to run.
     */
    PlainScene(
        Config const *config,
        Builder const *builder,
        Timer *timer,
        Radio *radio,
        Repository *repository,
        char const *script
    );
};

#endif
