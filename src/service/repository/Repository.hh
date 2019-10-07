#ifndef REPOSITORY_H
#define REPOSITORY_H

/**
 * Represents a repository of some class which can load them in and then cache
 * them for later use.
 */
template <class T> class Repository {
    public:
        /**
         * Deletes everything that is cached as well as this repository.
         */
        virtual ~Repository();

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
        Asset<T> *get(char const *name) {
            if (!this->items.contains(name)) {
                this->items[name] = this->create(name);
            }
            return this->items[name];
        }

        /**
         * Used to load an asset relative to the location of another asset.
         * From is the location of the first asset, and name is the name of the
         * asset relative to the first asset. For example, if from is
         * example/maps/big.tmx and name is tiles.tsx, the resulting name
         * should example/maps/tiles.tsx. Should also be able to handle going
         * back directories.
         * @param from is the full path of the first part.
         * @param name is the bit to add to the path.
         * @return the gotten asset.
         */
        Asset<T> *getRelative(char const *from, char const *name) {
            // TODO: some freaky path processing shit.
            return this->get(name);
        }

        /**
         * Recreates everything in the cache and updates the pointers in the
         * assets.
         */
        void zap() {
            for(auto const &name: this->items) {
            }
        }

    private:
        unordered_map<std::string, Asset<T>> items;

        /**
         * Create the object fresh.
         * @param name is the name of the thing to create which is often a file
         *        name but is not necessarily you know.
         */
        virtual T create(char const *name) = 0;
};

#endif
