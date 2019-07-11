#ifndef TIMER_H
#define TIMER_H

#include "interface/Listener.hh"
#include "static/Constant.hh"
#include <SFML/System.hpp>

/**
 * Takes care of running timing stuff.
 */
class Timer {
    /**
     * Behind the scenes datastructure for running timers. The idea is that a given time in the future (in ticks) is
     * registered along with a listener, and when that time is the current time they will be notified and removed.
     */
    class Wait {
    public:
        Listener *listener = 0;
        union {
            long time;
            Wait *next = 0;
        } content;
    };

    Wait timers[Constant::TIMER_LIMIT];
    Wait *emptyTimer;
    long tick;
    sf::Clock clock;

public:
    Timer();

    /**
     * Fires off any timers that need to be fired and monitors fps and stuff.
     */
    void update();

    /**
     * Starts a timer which will send a signal when done.
     * @param listener is the listener to inform when it is done.
     * @param time     is the number of ticks from now at which the timer is done.
     */
    void start(Listener *listener, long time);

    /**
     * Gives the current frame number.
     * @return the number of frames since the start of the game.
     */
    long getTick() const;
};

#endif
