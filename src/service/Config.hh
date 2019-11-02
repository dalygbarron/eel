#ifndef CONFIG_H
#define CONFIG_H

#include "interface/Store.hh"
#include <SFML/Graphics.hpp>

/**
 * Contains the game's base configuration values. This is the in engine
 * representation of the first file that is loaded and thus it must load the
 * file itself from wherever it is, and from that point be referred to in order
 * to find the root directory from which other files are referred to.
 */
class Config {
    public:
        constexpr static char const *NAME = "name";
        constexpr static char const *VERSION = "version";
        constexpr static char const *ENGINE = "engine";
        constexpr static char const *WIDTH = "width";
        constexpr static char const *HEIGHT = "height";

        /**
         * Creates the config object and loads in it's shit.
         * @param filename is the file that the config data should be read
         *                 from.
         */
        Config(char const &filename);

        /**
         * Clears out all the junk hell yeah.
         */
        ~Config();

        /**
         * Gives you the root directory of the game.
         * @return the root directory as a constant string.
         */
        char const &getRoot() const;

        /**
         * Writes a filename into the root directory.
         * @param buffer is where to write the string to. it is not length
         *               checked so deal with that yourself.
         * @param file   is the file to put in the root directory.
         * @return the number of characters written not including null
         *         terminator, or negative number on error.
         */
        int inRoot(char &buffer, char const &file) const;

        /**
         * Gives you the name of the game.
         * @return the name of the game.
         */
        char const &getName() const;

        /**
         * Gives you the game's version.
         * @return the version which is a piece of text.
         */
        char const &getVersion() const;

        /**
         * Gives the major engine version that the game needs.
         * @return the version number.
         */
        int getEngineMajor() const;

        /**
         * Gives the minor engine version that the game needs.
         * @return version number.
         */
        int getEngineMinor() const;

        /**
         * Gives the desired virtual screen dimensions.
         * @return the dimensions as a vector.
         */
        sf::Vector2i getDimensions() const;

    private:
        char &root;
        char &name;
        char &version;
        int engineMajor;
        int engineMinor;
        sf::Vector2i dimensions;

        /**
         * Loads the game config data in from a file and sets everything using
         * it.
         * @param filename is the name of the file to load from.
         */
        void parseXml(char const *filename);
};

#endif
