#ifndef CONFIG_H
#define CONFIG_H

#include "interface/Store.hh"

/**
 * Contains the game's base configuration values.
 */
class Config: public Store<char const *> {
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
         * @param buffer is where to write the string to. it is not length
         *               checked so deal with that yourself.
         * @param file   is the file to put in the root directory.
         * @return the number of characters written not including null
         *         terminator, or negative number on error.
         */
        int inRoot(char *buffer, char const *file) const;

        char const *getName() const;

        char const *getVersion() const;

        int getEngine() const;

        int getWidth() const;

        int getHeight() const;


    private:
        char *root;
        char *name;
        char *version;
        int engine;
        int width;
        int height;
};

#endif
