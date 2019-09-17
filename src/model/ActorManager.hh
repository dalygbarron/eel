#ifndef ACTOR_MANAGER_H
#define ACTOR_MANAGER_H

/**
 *
 */
class ActorManager {
    union {
        Actor actor;
        struct {
            int alive;
            Actor *next;
        };
    } actors[128];

};

#endif
