#ifndef LISTENER_H
#define LISTENER_H

#include "Signal.hh"

/**
 * Can register itself to receive info from about the place.
 */
class Listener {
    /**
     * Receive a signal from a speaker.
     * @param signal is the signal.
     */
    virtual int listen(Signal signal) = 0;
};

#endif
