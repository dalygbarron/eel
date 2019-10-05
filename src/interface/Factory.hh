#ifndef FACTORY_H
#define FACTORY_H

/**
 * A factory which builds some kind of asset.
 */
template <class T> class Factory {
    public:
        /**
         * Loads in a thing.
         * @param name is the name of the thing to load in.
         * @return the thing that has just been loaded in.
         */
        virtual T build(char const *name) = 0;
};

#endif
