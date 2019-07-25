#ifndef SCRIPT_H
#define SCRIPT_H

#include <lua.h>

/**
 * Basically just wraps around a lua script state and lets us store it's name.
 */ 
struct ScriptRunner {
    lua_State *state;
    lua_Thread *thread;
    int alive = false;
};

#endif
