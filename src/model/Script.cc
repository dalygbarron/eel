#include "model/Script.hh"
#include "model/control/Control.hh"
#include "model/control/Panel.hh"
#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include <lua5.3/lua.hpp>

void Script::showError(lua_State *state) {
    char const *message = lua_tostring(state, -1);
    spdlog::error("Lua Error: {}", message);
    lua_pop(state, 1);
}

void Script::listenToScene(Scene *scene, int type) {
    scene->addListener(this);
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

int Script::luaWait(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    double time = lua_tonumber(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    script->scene->engine->timer->start(script, floor(time));
    return 0;
}

int Script::luaDeclare(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    char const *text = lua_tostring(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    script->listenToScene(script->scene, Signal::TYPE_SCENE);
    Control *panel = script->scene->engine->controlBuilder->declarationBox(text);
    script->scene->addControl(panel);
    return 0;
}

int Script::luaListen(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 3);
    Scene *scene = (Scene *)Script::getLuaPointer(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    int type = floor(lua_tonumber(luaState, 3));
    script->listenToScene(scene, type);
    return 0;
}

int Script::luaTransition(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    char const *text = lua_tostring(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    int length = strlen(text);
    if (length > Constant::TRANSITION_BUFFER_SIZE - 2) {
        spdlog::error("Lua Error: transition message too long");
        return 0;
    }
    strcpy(script->scene->transition, text);
    return 0;
}

int Script::luaPlaySound(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    char const *name = lua_tostring(luaState, 1);
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    int frames = script->scene->engine->radio->playSound(name);
    lua_pushnumber(luaState, frames);
    return 1;
}

int Script::luaSetRefresh(lua_State *luaState) {
    Script::validateLuaArgs(luaState, 2);
    unsigned int colour = floor(lua_tonumber(luaState, 1));
    Script *script = (Script *)Script::getLuaPointer(luaState, 2);
    script->scene->bg = sf::Color(colour);
    spdlog::debug("Setting refresh to {:x}", colour);
    return 0;
}

Script::Script(Scene *scene, char const *file) {
    this->scene = scene;
    this->state = luaL_newstate();
    // declare my stuff in the lua context.
    luaL_openlibs(this->state);
    lua_register(this->state, "_wait", Script::luaWait);
    lua_register(this->state, "_declare", Script::luaDeclare);
    lua_register(this->state, "_transition", Script::luaTransition);
    lua_register(this->state, "_playSound", Script::luaPlaySound);
    lua_register(this->state, "_setRefresh", Script::luaSetRefresh);
    // Fix the path to go to the right joint.
    char filename[Constant::FILENAME_BUFFER_SIZE];
    sprintf(filename, "./%s/?.lua", scene->engine->config->getRoot());
    lua_getglobal(this->state, "package");
    lua_pushstring(this->state, filename);
    lua_setfield(this->state, -2, "path");
    lua_pop(this->state, 1);
    // load the file.
    int result = luaL_loadstring(this->state, file);
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

void Script::tick() {
    lua_pushlightuserdata(this->thread, (void *)this);
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

int Script::listen(Signal signal) {
    tick();
}
