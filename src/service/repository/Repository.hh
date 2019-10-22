#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "model/Asset.hh"
#include "model/Path.hh"
#include "static/spdlog/spdlog.h"
#include <unordered_map>
#include <string>

/**
 * Represents a repository of some class which can load them in and then cache
 * them for later use.
 */
template <class T> class Repository {
    public:
        Repository(char const *path) {
            this->root = path;
        }

        /**
         * Deletes everything that is cached as well as this repository.
         */
        ~Repository() {
            this->items.clear();
        }

        /**
         * Gets you something from the repository. If it is cached it returns
         * it from there, and if not it loads it and then stores it in the
         * cache for next time. If it is possible for the thing to not be
         * created then you will need to consult the implementation for details
         * but you will probably get a null pointer if it's a pointer type.
         * Null pointers are cached too so that we don't need to fail
         * repeatedly.
         * @param name is the name of the asset we seek.
         * @return the asset.
         */
        Asset<T> const *get(char const *name) const {
            if (this->items.count(name) == 0) {
                Path filename(this->root, name);
                Asset<T> *asset = new Asset<T>(this->create(
                    filename.get(),
                    name
                ));
                this->items[name] = asset;
            }
            return this->items[name];
        }

        /**
         * Loads something from file, adds it to the cache, and returns you
         * a mutable pointer to it. If the thing is already in the cache then
         * this does not work and it blows up.
         * @param name is the name of the thing to load.
         * @return the thing.
         */
        T *snatch(char const *name) {
            if (this->items.count(name) == 0) {
                Path filename(this->root, name);
                T *item = this->create(filename.get(), name);
                Asset<T> *asset = new Asset<T>(item);
                this->items[name] = asset;
                return item;
            } else {
                spdlog::error(
                    "Snatch must be first access to item '{}'",
                    name
                );
                throw -1;
            }
        }

        /**
         * Recreates everything in the cache and updates the pointers in the
         * assets.
         */
        void zap() {
            for(auto const &name: this->items) {
                delete this->items[name];
                Path path(this->root, name);
                this->items[name] = this->create(path.get(), name);
            }
        }

    private:
        mutable std::unordered_map<std::string, Asset<T> *> items;
        char const *root;

        /**
         * Create the object fresh.
         * @param filename is the filename to open the data from. It is not the
         *                 same as the key as it can have extra directories in
         *                 it.
         * @param key      is the key the file is named after. Useful for
         *                 to other repos and stuff like that.
         * @return a non const pointer to the new object.
         */
        virtual T *create(char const *filename, char const *key) const = 0;
};

#endif
