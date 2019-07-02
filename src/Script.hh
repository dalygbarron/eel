#ifndef SCRIPT_H
#define SCRIPT_H

#include "Listener.hh"
#include "Scene.hh"
#include <lua5.3/lua.hpp>

/**
 * Represents an external script that can be used to drive aspects of the engine for example the gui or enemy behavior.
 * If I ever need to implement a second scripting language I will move the lua specific stuff to a subclass but right
 * now it's not worth the effort.
 */
class Script: public Listener {
    lua_State *state = 0;
    lua_State *thread = 0;
    Scene *scene = 0;
    int alive = true;
    int listeningFor = -1;

    /**
     * Shows the most recent error in the script.
     * @param state is the lua state that caused the error since there are two in there.
     */
    void showError(lua_State *state);

    /**
     * Makes the script start listening to the given scene.
     * @param scene is the scene to listen to.
     * @param type  is the type of signals to listen for.
     */
    void listenToScene(Scene *scene, int type);

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

public:
    /**
     * Allows the script to connect itself up to a timer.
     * in: number of ticks to wait.
     * in: script.
     * @param luaState is the lua state from which this is happening.
     * @return the number of things put on the lua stack.
     */
    static int luaWait(lua_State *luaState);

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
     * Lua function to make a script listen to a scene for info.
     * in: pointer to scene.
     * in: pointer to script.
     * in: type of signal to lsiten to.
     * @param luaState is the lua state that called this.
     * @return the number of items returned.
     */
    static int luaListen(lua_State *luaState);

    /**
     * Creates the script from a source file.
     * @param scene is the scene that the script is operating in.
     * @param file  is the file containing the script content.
     * TODO: probably better to load and compile seperately and use it for each instance of given script.
     */
    Script(Scene *scene, char const *file);

    /**
     * Deletes the script and it's junk.
     */
    ~Script();

    /**
     * Run the script for one go until it yields.
     */
    void tick();

    /**
     * Tells you if the given script instance can still run or if it is done.
     * @return true if the script is not over, and false if it is over.
     */
    int isAlive();

    virtual int listen(Signal signal) override;
};

#endif
