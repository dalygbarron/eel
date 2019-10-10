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

        /**
         * Creates the asset thingy and populates it's content.
         * @param content is the content to put in it.
         */
        Asset(T *content) {
            this->content = content;
        }

        /**
         * Deletes the asset's content.
         */
        ~Asset() {
            delete this->content;
        }

        /**
         * Gives the actual asset inside this. Don't just use this to strip out
         * the meat and eat it, you need to keep this asset object whenever
         * possible so that the asset you are holding can be reloaded live.
         * @return a const pointer to your nice asset.
         */
        T const *get() {
            return this->content;
        }

    private:
        T *content;
};

#endif
