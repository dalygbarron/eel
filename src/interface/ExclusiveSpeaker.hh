#ifndef EXCLUSIVE_SPEAKER_H
#define EXCLUSIVE_SPEAKER_H

#include "interface/Listener.hh"
#include <list>

/**
 * A speaker that maintains a stack of it's registered listeners, and only sends it's events to the topmost one, then
 * feeding it down the stack when it is rejected by the higher ups.
 */
class ExclusiveSpeaker {
    std::list<Listener *> listeners;

public:
    /**
     * Adds a listener to the top of the stack.
     * @param listener is the listener to add.
     */
    void addListener(Listener *listener);

    /**
     * Sends a signal to the first listener that will accept it working from the top of the stack.
     * @param signal is the signal to send.
     */
    void speak(Signal signal);
};

#endif
