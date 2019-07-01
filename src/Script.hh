#ifndef SCRIPT_H
#define SCRIPT_H

#include "Listener.hh"
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

public:
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
