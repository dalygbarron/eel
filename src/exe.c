#include "exe.h"
#include "log.h"
#include <luajit-2.0/lua.h>
#include <luajit-2.0/lualib.h>
#include <luajit-2.0/lauxlib.h>

#define RUNNER_SCRIPT_ADD "addScript"
#define RUNNER_SCRIPT_LISTEN "listen"

static void showError(lua_State *state) {
    char const *message = lua_tostring(state, -1);
    log_error(message);
    lua_pop(state, 1);
}

int exe_initScriptRunner(struct ScriptRunner *scriptRunner) {
    lua_State *state;
    scriptRunner->state = state;
    luaL_openlibs(state);
    // This would be where bindings are added but I do not have any yet.
    // This would be where the include path is set to the game directory.
    // TODO: link in lua script somehow.
    int result = luaL_loadstring(state, "print('hello')");
    if (result) {
        showError(state);
        return 0;
    }
    lua_pcall(state, 0, 0, 0);
    return 1;
}

int exe_initScript(struct ScriptRunner *scriptRunner, char const *script) {
    int result = exe_initScriptRunner(scriptRunner);
    if (result) result = exe_addScript(scriptRunner, script);
    return result;
}

int exe_addScript(struct ScriptRunner *scriptRunner, char const *script) {
    // TODO: this.
    return 1;
}

void exe_run(struct ScriptRunner *scriptRunner) {
}

void exe_listen(struct ScriptRunner *scriptRunner, int script, int value) {
    lua_pushnumber(scriptRunner->thread, script);
    lua_pushnumber(scriptRunner->thread, value);
    lua_pushlightuserdata(scriptRunner->thread, (void *)scriptRunner);
    int result = lua_resume(scriptRunner->thread, 0);
    if (!result) {
        lua_close(scriptRunner->state);
    } else if (result != LUA_YIELD) {
        showError(scriptRunner->thread);
    }
}
