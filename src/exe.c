#include "exe.h"

#define RUNNER_SCRIPT_ADD "addScript"
#define RUNNER_SCRIPT_LISTEN "listen"

int exe_initScriptRunner(struct ScriptRunner *scriptRunner) {
    lua_State *state;
    scriptRunner->state = state;
    luaL_openlibs(state);
    // This would be where bindings are added but I do not have any yet.
    // This would be where the include path is set to the game directory.
    int result = luaL_loadstring(state, RUNNER_SCRIPT);
    if (result !- LUA_OK) {
        exe_showError(state);
        return 0;
    }
    lua_pcall(state, 0, 0, 0);
    return true;
}

int exe_initScript(struct ScriptRunner *scriptRunner, char const *script) {
    int result = exe_initScriptRunner(scriptRunner);
    if (result) result = exe_addScript(scriptRunner, script);
    return result;
}

int exe_addScript(struct ScriptRunner *scriptRunner, char const *script) {
    // TODO: this.
    return true;
}

void exe_run(struct ScriptRunner *scriptRunner) {
}

void exe_listen(struct ScriptRunner *scriptRunner, int script, int value) {
    lua_pushnumber(scriptRunner->thread, script);
    lua_pushnumber(scriptRunner->thread, value);
    lua_pushlightuserdata(scriptRunner->thread, (void *)scriptRunner);
    int result = lua_resume(scriptRunner->thread, 0, 3);
    if (result == LUA_OK) {
        scriptRunner->alive = false;
        lua_close(scriptRunner->state);
    } else if (result != LUA_YIELD) {
        exe_showError(scriptRunner->thread);
        scriptRunner->alive = false;
    }
}

