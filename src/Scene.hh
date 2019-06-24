#ifndef SCENE_H
#define SCENE_H

#include "Control.hh"
#include <list>
#include <SFML/Graphics.hpp>

class Scene;

/**
 * Represents some phase of the overall game for example the part where you are in the level and playing, or the main
 * menu or some other thing like that.
 */
class Scene: public sf::Drawable {
    Control *gui = 0;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * Draws the actual content in the scene.
     * @param target is the render target that we are rendering onto.
     * @param states is the rendering state thingy that must be given textures and shit.
     */
    virtual void render(sf::RenderTarget &target, sf::RenderStates states) const = 0;

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
     * Updates the scene as should be called every frame.
     */
    void update();

    /**
     * Adds a gui widget to this scene.
     * @param widget is the widget added. NOTE: after use it will be deleted by the scene.
     */
    void addControl(Control *widget);

    /**
     * Sends an event to the scene's gui widgets if it has any.
     * @param event is the event to send.
     */
    void onEvent(sf::Event *event);
};

#endif
