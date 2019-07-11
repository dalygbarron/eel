#ifndef LISTENER_H
#define LISTENER_H

#include "model/Signal.hh"

/**
 * Can register itself to receive info from about the place.
 */
class Listener {
public:
    /**
     * Receive a signal from a speaker.
     * @param signal is the signal.
     * @return true if the signal was used, or false to say you didn't want it and someone else can have it.
     */
    virtual int listen(Signal signal) = 0;
};

#endif
