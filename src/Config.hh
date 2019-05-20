#ifndef CONFIG_H
#define CONFIG_H

/**
 * Contains some general variables of the project that are not really the kind you put in a configuration file.
 */
namespace Config {
    /**
     * The game has a constant frame rate and this is it.
     */
    int const FRAME_RATE = 60;

    /**
     * Maximum number of bullets allowed at a time.
     */
    int const BULLET_LIMIT = 2048;

};

#endif
