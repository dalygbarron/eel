#ifndef SCRIPT_H
#define SCRIPT_H

#include <luajit-2.0/lua.h>
#include <luajit-2.0/lualib.h>
#include <luajit-2.0/lauxlib.h>

/**
 * Basically just wraps around a lua script state and thread.
 */ 
struct ScriptRunner {
    lua_State *state;
    lua_State *thread;
};

#endif
