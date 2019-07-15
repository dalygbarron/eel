#ifndef JUMP_SCENE_H
#define JUMP_SCENE_H

#include "model/scene/JumpScene.hh"

/**
 * Scene where there are fellows that jump hell yeah.
 */
class JumpScene: public JumpScene {
    std::forward_list<Actor *> actors;
    

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual void logic(long tick) override;

public:
    /**
     * Makes the jumping scene.
     * @param engine is the engine that the scene has need of.
     */
    JumpScene(Engine const *engine);
};

#endif
