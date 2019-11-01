#ifndef SCENE_H
#define SCENE_H

#include "model/control/Control.hh"
#include "service/Engine.hh"
#include "static/Constant.hh"
#include <SFML/Graphics.hpp>

/**
 * Represents some phase of the overall game for example the part where you are
 * in the level and playing, or the main menu or some other thing like that.
 */
class Scene: public sf::Drawable {
    public:
        Engine const &engine;
        char transition[Constant::TRANSITION_BUFFER_SIZE];
        sf::Color bg = sf::Color(0);

        /**
         * Point at which scene is created.
         * @param engine are the game engine services for the scene to make use
         *               of.
         */
        Scene(Engine const &engine);

        /**
         * Deletes the scene and it's shit.
         */
        virtual ~Scene();

        /**
         * Updates the scene as should be called every frame.
         * @param delta is the time since the last frame.
         * @param mouse is a bunch of bits representing what mouse buttons were
         *              clicked last frame.
         */
        void update(float delta, unsigned char mouse);

        /**
         * Adds a gui widget to this scene.
         * @param widget is the widget added. NOTE: after use it will be
         *               deleted by the scene.
         */
        void addControl(Control &widget);

        /**
         * Gives you the result of the last gui box.
         * @return the result number which is 0 or greater.
         */
        int getResult() const;

    private:
        Control *gui = 0;
        int result = -1;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;

        /**
         * This scene's actual logic implementation.
         * @param delta is the time since the last tick.
         */
        virtual void logic(float delta) = 0;
};

#endif
