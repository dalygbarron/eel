#ifndef SCENE_H
#define SCENE_H

#include <list>
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
    Widget *gui = 0;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * Draws the actual content in the scene.
     * @param target is the render target that we are rendering onto.
     * @param states is the rendering state thingy that must be given textures and shit.
     */
    virtual void drawContent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    /**
     * This scene's actual logic implementation.
     */
    virtual void logic() = 0;

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
    void update(Transition *transition);

    /**
     * Adds a gui widget to this scene.
     * @param widget is the widget added. NOTE: after use it will be deleted by the scene.
     */
    void addWidget(Widget *widget);
};

#endif
