#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>


class Scene;

/**
 * Data structure for storing what should happen after the current update of the scene.
 */
class Transition {
public:
    static int const NOTHING = 0;
    static int const POP = 1;
    static int const PUSH = 2;
    static int const REPLACE = 3;

    int action = 0;
    Scene *scene = 0;
};

/**
 * Represents some phase of the overall game for example the part where you are in the level and playing, or the main
 * menu or some other thing like that.
 */
class Scene: public sf::Drawable {
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /**
     * Point at which scene is created.
     */
    Scene();

    /**
     * Updates the scene as should be called every frame unless there is a gui going on or something.
     * @param transition is sent from the main process and what you set it to determines the fate of this scene. If
     *                   action is set to Transition::NOTHING it is expected nothing will happen, if it is set to
     *                   Transition::POP it is expected the current scene will be removed from the stack. If it is set
     *                   to Transition::PUSH it is expected the given scene will be pushed to the stack, and if it is
     *                   set to Transition::REPLACE then it is expected that the current scene will be popped from the
     *                   stack and then the given scene will be pushed onto the scene stack.
     */
    virtual void update(Transition *transition) = 0;
};

#endif
