#ifndef ASSET_H
#define ASSET_H

/**
 * Represents access to an asset. Whenever you are in your own bit of code the
 * value of content will not change, however, it can change whenever so you
 * must be prepared.
 * The reason for this is it allows us to hot reload assets which is pretty
 * cool if I do say so myself.
 * Since Tilesets are also their own kind of asset, in a hot reload they too
 * will need to be reloaded which means that they will know their new
 * dependencies automatically so don't worry about that.
 */
template <class T> class Asset {
    public:
        T content;

        /**
         * Deletes the asset's content.
         */
        ~Asset() {
            delete this->content;
        }
};

#endif
