#ifndef SCENE_H
#define SCENE_H

#include "model/control/Control.hh"
#include "service/Engine.hh"
#include <SFML/Graphics.hpp>

/**
 * Represents some phase of the overall game for example the part where you are
 * in the level and playing, or the main menu or some other thing like that.
 */
class Scene: public sf::Drawable {
    public:
        Engine const *engine;
        char transition[Constant::TRANSITION_BUFFER_SIZE];
        sf::Color bg = sf::Color(0);

        /**
         * Point at which scene is created.
         * @param engine are the game engine services for the scene to make use
         *               of.
         */
        Scene(Engine const *engine);

        /**
         * Deletes the scene and it's shit.
         */
        virtual ~Scene();

        /**
         * Updates the scene as should be called every frame.
         * @param delta is the time since the last frame.
         */
        void update(float delta);

        /**
         * Adds a gui widget to this scene.
         * @param widget is the widget added. NOTE: after use it will be
         *               deleted by the scene.
         */
        void addControl(Control *widget);

    private:
        Control *gui = 0;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;

        /**
         * This scene's actual logic implementation.
         * @param delta is the time since the last tick.
         */
        virtual void logic(float delta) = 0;

        /**
         * Draws the actual content in the scene.
         * @param target is the render target that we are rendering onto.
         * @param states are the renderer states to set up as needed.
         */
        virtual void render(
            sf::RenderTarget *target,
            sf::RenderStates states
        ) const = 0;
};

#endif
