#include "Script.hh"
#include <iostream>
#include <lua5.3/lua.hpp>

void Script::showError(lua_State *state) {
    char const *message = lua_tostring(state, -1);
    std::cerr << message << std::endl;
    lua_pop(state, 1);
}

Script::Script(char const *file) {
    this->state = luaL_newstate();
    luaL_openlibs(this->state);
    int result = luaL_loadfile(this->state, file);
    if (result != LUA_OK) {
        showError(this->state);
        throw -1;
    }
    lua_pcall(this->state, 0, 0, 0);
    this->thread = lua_newthread(this->state);
    lua_getglobal(this->thread, "main");
}

Script::~Script() {
    // not much going on here.
    // TODO: there's probably something I can delete I dunno.
}

void Script::tick() {
    int result = lua_resume(this->thread, 0, 0);
    if (result == LUA_OK) {
        this->alive = false;
        lua_close(state);
    } else if (result != LUA_YIELD) {
        showError(this->thread);
        this->alive = false;
    }
}

int Script::isAlive() {
    return this->alive;
}
