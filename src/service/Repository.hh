#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "service/Config.hh"
#include "model/SpriteBatch.hh"
#include "model/Tileset.hh"
#include "model/TileMap.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

/**
 * Loads assets out of files and then keeps them stored for later.
 * Could potentially add strategic dropping of little used data if memory 
 * usage is an issue but I doubt that.
 */
template <class T> class Repository {
    public:
        Repository(Factory<T> factory) {
            this->factory = factory;
        }

        T get(char const *name) {
            if (!this->cache.contains(name)) {
                cache[name] = this->factory.build(name);
            }
            return this->cache[name]
        }

    private:
        std::unordered_map<std::string, T> cache;
        Factory<T> factory;
};

#endif
