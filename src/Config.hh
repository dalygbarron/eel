#ifndef CONFIG_H
#define CONFIG_H

/**
 * Contains hard coded config settings that would be painful to store in the game config file and don't really need to
 * be changed anyway.
 */
namespace Config {
    int const FPS = 60;
    int const BULLET_LIMIT = 2048;
    int const FILENAME_BUFFER_SIZE = 64;
    static char const *DEFAULT_GAME_FILE = "game.ini";
    static char const *BULLET_FILE = "bullets";
    static char const *FISH_FILE = "fishes";
};

#endif
