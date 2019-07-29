#ifndef CONFIG_H
#define CONFIG_H

/**
 * Stores the game's parameters
 */
struct Config {
    /** The width that the game screen should have */
    int screenWidth;

    /** The height that the game screen should have */
    int screenHeight;

    /** The title that the game window should show */
    char *title;

    /** The transition that will start the game */
    char *start;
};

#endif
