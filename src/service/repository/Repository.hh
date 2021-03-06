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
        /**
         * Creates the repo.
         * @param path is the root directory from which files are found.
         */
        Repository(char const &path): root(&path) {
            // does nothing else.
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
         * cache for next time.
         * @param name is the name of the asset we seek.
         * @return the asset.
         */
        Asset<T> const &get(char const &name) const {
            this->find(name);
            return this->items.at(&name);
        }

        /**
         * Loads something from cache / file, and returns you the
         * thing itself in a mutable form.
         * @param name is the name of the thing to load / get.
         * @return the thing.
         */
        T &snatch(char const &name) {
            this->find(name);
            return this->items.at(&name).getMutable();
        }

        /**
         * Recreates everything in the cache and updates the pointers in the
         * assets.
         */
        void zap() {
            for (auto const &name: this->items) {
                delete this->items[name];
                Path path(*this->root.c_str(), name);
                this->items[&name] = this->create(path.get(), name);
            }
        }

    private:
        mutable std::unordered_map<std::string, Asset<T>> items;
        std::string const root;

        /**
         * Looks for a given key in the cache and creates it if it's not there.
         */
        void find(char const &name) const {
            if (this->items.count(&name) == 0) {
                Path filename(*this->root.c_str(), name);
                T *item = this->create(filename.get(), name);
                if (!item) {
                    throw new std::domain_error("couldn't create item");
                }
                this->items.emplace(&name, *item);
            }
        }

        /**
         * Create the object fresh.
         * @param filename is the filename to open the data from. It is not the
         *                 same as the key as it can have extra directories in
         *                 it.
         * @param key      is the key the file is named after. Useful for
         *                 to other repos and stuff like that.
         * @return a non const pointer to the new object which is null if it
         *         could not be created.
         */
        virtual T *create(char const &filename, char const &key) const = 0;
};

#endif
