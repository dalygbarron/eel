#ifndef BUILDER_H
#define BUILDER_H

#include "../Control.hh"
#include "../Config.hh"
#include "../Repository.hh"
#include "../Utils.hh"

/**
 * Puts gui windows together according to your specifications.
 */
class Builder {
    Config const *config;
    Repository *repository;

    /**
     * Makes the builder and injects dependencies.
     * @param config     is the game's base configuration.
     * @param repository is the game's source of assets to use.
     */
    Builder(Config const *config, Repository *repository);
};

#endif
