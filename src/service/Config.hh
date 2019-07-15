#ifndef CONFIG_H
#define CONFIG_H

#include "interface/Store.hh"
#include <string>

/**
 * Contains the game's base configuration values.
 */
class Config: public Store<char const *> {
    char *root;

public:
    /**
     * Creates config object.
     * @param file is the file in which the game configuration is stored.
     */
    Config(char const *file);

    /**
     * Clears out all the junk hell yeah.
     */
    ~Config();

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
     * Callback function used to populate the config data from an ini file.
     * @param reference is a reference to the config object.
     * @param section   is the section that the current piece of data was in.
     * @param name      is the name of the current piece of data to add.
     * @param value     is the value of the current piece of data to add.
     * @return 1 if all is going well, and another value if not.
     */
    static int handleIni(void *reference, char const *section, char const *name, char const *value);
};

#endif
