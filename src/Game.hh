#ifndef GAME_H
#define GAME_H

#include "Store.hh"
#include <string>
#include "Repository.hh"

/**
 * Contains the game's base configuration values.
 */
class Game: public Store<char const *> {
    Repository const *repository;

public:
    /**
     * Creates game object.
     * @param repo is the asset repository which is used by the game to load assets.
     * @param file is the file in which the game configuration is stored.
     */
    Game(Repository const *repo, char const *file);

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
