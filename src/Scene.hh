#ifndef SCENE_H
#define SCENE_H

#include "Control.hh"
#include "ExclusiveSpeaker.hh"
#include "Builder.hh"
#include "Timer.hh"
#include "Radio.hh"
#include <list>
#include <SFML/Graphics.hpp>

class Scene;

/**
 * Represents some phase of the overall game for example the part where you are in the level and playing, or the main
 * menu or some other thing like that.
 */
class Scene: public sf::Drawable, public ExclusiveSpeaker {
    Control *gui = 0;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * This scene's actual logic implementation.
     * @param tick       is the frame number.
     */
    virtual void logic(long tick) = 0;

    /**
     * Draws the actual content in the scene.
     * @param target is the render target that we are rendering onto.
     * @param states are the renderer states to set up as needed.
     */
    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const = 0;

public:
    /**
     * Encapsulates gamewide services as needed by scenes.
     */
    class Engine {
        Config const *config;
        Builder const *builder;
        Timer *timer;
        Radio *radio;
    };

    Engine const *engine;
    char transition[Constant::TRANSITION_BUFFER_SIZE];
    sf::Color bg = sf::Color(0);

    /**
     * Point at which scene is created.
     * @param engine are the game engine services for the scene to make use of.
     */
    Scene(Engine const *engine);

    /**
     * Updates the scene as should be called every frame.
     * @param tick       is the frame number.
     */
    void update(long tick);

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
