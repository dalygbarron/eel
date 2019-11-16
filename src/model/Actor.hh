#ifndef ACTOR_H
#define ACTOR_H

#include "model/Mob.hh"
#include "model/Persona.hh"

/**
 * Represents a general dude who can participate in a bullet hell scene and
 * maybe other scenes too. They are only for moving around in two dimensions
 * right now. If you want three dimenswions maybe make a new class.
 */
class Actor: public Mob {
public:
    /**
     * Turns this actor into an instance of the given prototype.
     * @param proto   is the prototype to emulate.
     */
    void restore(Persona &proto);

    /**
     * Performs the actors logic stuff.
     * @param delta is the amount of time passed since the last frame in
     *              seconds.
     */
    void logic(float delta);
};

#endif
