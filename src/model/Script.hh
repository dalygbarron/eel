#ifndef SCRIPT_H
#define SCRIPT_H

#include "scene/Scene.hh"
#include <lua5.3/lua.hpp>

/**
 * Represents a script which can control stuff. They should be run every update
 * frame and if they want to wait for something to happen they should loop and
 * poll and yield. No event listeners.
 */
class Script {
    public:
        /**
         * Creates the script from a source file.
         * @param scene  is the scene that the script is operating in.
         * @param text is the text of the script.
         */
        Script(Scene &scene, char const &text);

        /**
         * Deletes the script and it's junk.
         */
        ~Script();

        /**
         * Run the script for one go until it yields.
         * @param delta is the passage of time since last tick.
         */
        void tick(float delta);

        /**
         * Tells you if the given script instance can still run or if it is
         * done.
         * @return true if the script is not over, and false if it is over.
         */
        int isAlive();

    private:
        lua_State *state = 0;
        lua_State *thread = 0;
        Scene &scene;
        int alive = true;
        int virgin = true;

        /**
         * Shows the most recent error in the script.
         * @param state is the lua state that caused the error since there are
         *              two in there.
         */
        void showError(lua_State *state);

        /**
         * Validates that the arguments to a lua function are all good.
         * @param luaState is the calling lua thingy.
         * @param n        is the number of arguments it should have.
         * @return true if all good and false if not.
         */
        static int validateLuaArgs(lua_State *luaState, int n);

        /**
         * Gets a pointer off a lua stack and makes sure it's not null.
         * @param luaState is the state to get it from.
         * @param index    is the index in the stack.
         * @return the pointer.
         */
        static void *getLuaPointer(lua_State *luaState, int index);

        /**
         * Lua function to add a speech box to the current scene.
         * in: name.
         * in: text.
         * in: pointer to script.
         * out: pointer to new text box.
         * @param luaState is the luaState that has called this.
         * @return the number of items returned.
         */
        static int luaSay(lua_State *luaState);

        /**
         * Lua function to add a text box to the current scene.
         * in: text.
         * in: pointer to script.
         * out: pointer to new text box.
         * @param luaState is the luaState that has called this.
         * @return the number of items returned.
         */
        static int luaDeclare(lua_State *luaState);

        /**
         * Tell the scene to transition to a new scene after the next frame.
         * in: pointer to script.
         * in: scene transition text.
         * @param luaState is the lua state that called this.
         * @return the number of things returned.
         */
        static int luaTransition(lua_State *luaState);

        /**
         * Plays a sound.
         * in: pointer to script.
         * in: name of sound.
         * out: number of frames the sound should take to play.
         * @param luaState is the calling lua state thingy.
         * @return the number of things returned to lua.
         */
        static int luaPlaySound(lua_State *luaState);

        /**
         * Sets the screen refresh colour for the given script's scene.
         * @param luaState is the state of the script doing this.
         * @return the number of return values put on the stack.
         */
        static int luaSetRefresh(lua_State *luaState);
};

#endif
