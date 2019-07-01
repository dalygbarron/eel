#ifndef BUILDER_H
#define BUILDER_H

#include "../Control.hh"
#include "../Config.hh"
#include "../Utils.hh"

/**
 * Puts gui windows together according to your specifications.
 */
class Builder {
    Config const *config;

    /**
     * Makes the builder and injects dependencies.
     * @param config is the game's base configuration.
     */
    Builder(Config const *config);
};

#endif
