#include "interface/ExclusiveSpeaker.hh"

void ExclusiveSpeaker::addListener(Listener *listener) {
    this->listeners.push_front(listener);
}

void ExclusiveSpeaker::speak(Signal signal) {
    for (Listener *listener: this->listeners) {
        // TODO: maybe they should be removed now.
        if (listener->listen(signal)) return;
    }
}
