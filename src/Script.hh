#ifndef SCRIPT_H
#define SCRIPT_H

#include <lua5.3/lua.hpp>

/**
 * Represents an external script that can be used to drive aspects of the engine for example the gui or enemy behavior.
 * If I ever need to implement a second scripting language I will move the lua specific stuff to a subclass but right
 * now it's not worth the effort.
 * When we have GUI scripts, there are often going to be times when a single script is going to want to take control and
 * put every other script in the background, like for example when a character speaks everything stops except for them
 * speaking. The way that this can be acheived is to add some c function which adds a script into a special holder in
 * the scene or whatever, and when some script is in this holder no other logic gets updated, and we also add a function
 * to remove it from the holder when it is done.
 */
class Script {
    lua_State *state = 0;
    lua_State *thread = 0;
    int alive = true;

    /**
     * Shows the most recent error in the script.
     * @param state is the lua state that caused the error since there are two in there.
     */
    void showError(lua_State *state);

public:
    /**
     * Creates the script from a source file.
     * @param file is the file containing the script content.
     * TODO: probably better to load and compile seperately and use it for each instance of given script.
     */
    Script(char const *file);

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
};

#endif
