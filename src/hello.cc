#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <lua5.3/lua.hpp>

int howdy(lua_State* state) {
  // The number of function arguments will be on top of the stack.
  int args = lua_gettop(state);

  printf("howdy() was called with %d arguments:\n", args);

  for ( int n=1; n<=args; ++n) {
    printf("  argument %d: '%s'\n", n, lua_tostring(state, n));
  }

  // Push the return value on top of the stack. NOTE: We haven't popped the
  // input arguments to our function. To be honest, I haven't checked if we
  // must, but at least in stack machines like the JVM, the stack will be
  // cleaned between each function call.

  lua_pushnumber(state, 123);

  // Let Lua know how many return values we've passed
  return 1;
}

void print_error(lua_State* state) {
    // The error message is on top of the stack.
    // Fetch it, print it and then pop it off the stack.
    const char* message = lua_tostring(state, -1);
    puts(message);
    lua_pop(state, 1);
}

void execute(const char* filename) {
    lua_State *state = luaL_newstate();
    luaL_openlibs(state);
    lua_register(state, "howdy", howdy);
    int result = luaL_loadfile(state, filename);
    if (result != LUA_OK) {
        print_error(state);
        return;
    }
    // now execute.
    lua_pcall(state, 0, 0, 0);
    lua_State *sub = lua_newthread(state);
    lua_getglobal(sub, "main");
    // loop on coroutine.
    while (true) {
        result = lua_resume(sub, 0, 0);
        if (result != LUA_OK && result != LUA_YIELD) {
            print_error(sub);
            break;
        }
        printf("got %f\n", lua_tonumber(sub, lua_gettop(sub)));
    }
    // finished.
    lua_close(state);
}

int main(int argc, char** argv) {
    if ( argc <= 1 ) {
        puts("Usage: runlua file(s)");
        puts("Loads and executes Lua programs.");
        return 1;
    }

    // Execute all programs on the command line
    for ( int n=1; n<argc; ++n ) {
        execute(argv[n]);
    }

    return 0;
}
