#ifndef GAME_H
#define GAME_H

#include "Store.hh"
#include <string>

/**
 * Contains the game's base configuration values.
 */
class Game: public Store<char const *> {
    char *root;

public:
    /**
     * Creates game object.
     * @param file is the file in which the game configuration is stored.
     */
    Game(char const *file);

    /**
     * Clears out all the junk hell yeah.
     */
    ~Game();

    /**
     * Gives you the root directory of the game.
     * @return the root directory as a constant string.
     */
    char const *getRoot() const;

    /**
     * Writes a filename into the root directory.
     * @param buffer is where to write the string to. it is not length checked so deal with that yourself.
     * @param file   is the file to put in the root directory.
     * @return the number of characters written not including null terminator, or negative number on error.
     */
    int inRoot(char *buffer, char const *file) const;

    /**
     * Callback function used to populate the game's data from an ini file.
     * @param reference is a reference to the game object.
     * @param section   is the section that the current piece of data was in.
     * @param name      is the name of the current piece of data to add.
     * @param value     is the value of the current piece of data to add.
     * @return 1 if all is going well, and another value if not.
     */
    static int handleIni(void *reference, char const *section, char const *name, char const *value);
};

#endif
