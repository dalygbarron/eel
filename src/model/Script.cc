#include "model/Script.hh"
#include "model/control/Control.hh"
#include "model/control/Panel.hh"
#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include <lua5.3/lua.hpp>

Script::Script(Scene &scene, char const &data): scene(scene) {
    this->state = luaL_newstate();
    // declare my stuff in the lua context.
    luaL_openlibs(this->state);
    lua_register(this->state, "_say", Script::luaSay);
    lua_register(this->state, "_declare", Script::luaDeclare);
    lua_register(this->state, "_transition", Script::luaTransition);
    lua_register(this->state, "_playSound", Script::luaPlaySound);
    lua_register(this->state, "_setRefresh", Script::luaSetRefresh);
    // Fix the path to go to the right joint.
    // TODO: this is still dodgy. Fix one day.
    Path path(*scene.engine.root.c_str(), *"?.lua");
    lua_getglobal(this->state, "package");
    lua_pushstring(this->state, &path.get());
    lua_setfield(this->state, -2, "path");
    lua_pop(this->state, 1);
    // load the file.
    int result = luaL_loadstring(this->state, &data);
    if (result != LUA_OK) {
        showError(this->state);
        throw -1;
    }
    // call main function with scene and script pointers.
    lua_pcall(this->state, 0, 0, 0);
    this->thread = lua_newthread(this->state);
    lua_getglobal(this->thread, Constant::SCRIPT_ENTRY);
}

Script::~Script() {
    // not much going on here.
    // TODO: there's probably something I can delete I dunno.
}

void Script::tick(float delta) {
    if (this->virgin) {
        lua_pushlightuserdata(this->thread, (void *)this);
        this->virgin = false;
    } else {
        lua_pushnumber(this->thread, delta);
    }
    int result = lua_resume(this->thread, 0, 1);
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

void Script::showError(lua_State *state) {
    char const *message = lua_tostring(state, -1);
    spdlog::error("Lua Error: {}", message);
    lua_pop(state, 1);
}

int Script::validateLuaArgs(lua_State *luaState, int n) {
    if (lua_gettop(luaState) != n) {
        lua_pushstring(luaState, "Lua call error: invalid arguments");
        lua_error(luaState);
        return false;
    }
    return true;
}

void *Script::getLuaPointer(lua_State *luaState, int index) {
    void *pointer = lua_touserdata(luaState, index);
    if (!pointer) {
        lua_pushstring(luaState, "Lua call error: null pointer");
        lua_error(luaState);
    }
    return pointer;
}

int Script::luaSay(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 3);
    char const *name = lua_tostring(luaState, 1);
    char const *text = lua_tostring(luaState, 2);
    Script *script = (Script *)Script::getLuaPointer(luaState, 3);
    if (!(name && text && script)) {
        spdlog::error("Lua Error: Incorrect usage of luaSay");
        return 1;
    }
    Control &panel = script->scene.engine.controlBuilder.speechBox(
        *name,
        *text
    );
    script->scene.addControl(panel);
    return 0;
}

int Script::luaDeclare(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    char const *text = lua_tostring(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    if (!(text && script)) {
        spdlog::error("Lua Error: Incorrect usage of luaDeclare");
        return 1;
    }
    Control &panel = script->scene.engine.controlBuilder.declarationBox(*text);
    script->scene.addControl(panel);
    return 0;
}

int Script::luaTransition(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    char const *text = lua_tostring(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    if (!(text && script)) {
        spdlog::error("Lua Error: Incorrect usage of luaTransition");
        return 1;
    }
    int length = strlen(text);
    if (length > Constant::TRANSITION_BUFFER_SIZE - 2) {
        spdlog::error("Lua Error: transition message too long");
        return 0;
    }
    strcpy(script->scene.transition, text);
    return 0;
}

int Script::luaPlaySound(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    char const *name = lua_tostring(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    if (!(name && script)) {
        spdlog::error("Lua Error: Incorrect usage of luaPlaySound");
        return 1;
    }
    float length = script->scene.engine.radio.playSound(*name);
    lua_pushnumber(luaState, length);
    return 1;
}

int Script::luaSetRefresh(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    unsigned int colour = floor(lua_tonumber(luaState, 1));
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    if (!script) {
        spdlog::error("Lua Error: Incorrect usage of luaSetRefresh");
        return 1;
    }
    script->scene.bg = sf::Color(colour);
    spdlog::debug("Setting refresh to {:x}", colour);
    return 0;
}
