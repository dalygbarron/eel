#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "model/Mob.hh"
#include "model/Item.hh"

/**
 * Represents the placement of a type of item into the world.
 */
class Placement: public Mob {
    public:
        Item *type;

};

#endif
