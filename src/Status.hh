#ifndef STATUS_H
#define STATUS_H

#include <unordered_map>

/**
 * Contains the current state of the game.
 */
class Status {
    unordered_map<std::string, int> counters;

public:
    int getCounter(char *name);

    void setCounter(char *name, int value);

};

#endif
