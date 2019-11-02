#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

/**
 * Contains the game's base configuration values. This is the in engine
 * representation of the first file that is loaded and thus it must load the
 * file itself from wherever it is, and from that point be referred to in order
 * to find the root directory from which other files are referred to.
 */
class Config {
    public:
        constexpr static char const *OPTION_SPRITESHEET = "spritesheet";
        constexpr static char const *OPTION_TILESET_SLOT = "tileset-slot";

        std::string const name;
        std::string const version;
        int const engineMajor;
        int const engineMinor;
        sf::Vector2f const dimensions;

        /**
         * Creates the config object and loads in it's shit.
         * @param filename is the file that the config data should be read
         *                 from.
         */
        Config(
            char const &name,
            char const &version,
            int engineMajor,
            int engineMinor,
            int width,
            int height
        );

        /**
         * Deletes all the option strings and stuff like that.
         */
        ~Config();

        /**
         * Gives you the value of a game option.
         * @param name is the name of the option to get.
         * @return the name which should last as long as the config object
         *         which should be basically the whole length of the game so
         *         you will be fine.
         * @throws domain_error if there is no option with that name.
         */
        char const &getOption(char const &name) const;

        /**
         * adds an option to the configuration.
         * @param name  is the name to put the option under.
         * @param value is the value the option should have.
         */
        void addOption(char const &name, char const &value);

    private:
        std::unordered_map<std::string, std::string> options;
};

#endif
