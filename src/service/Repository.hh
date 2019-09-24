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
class Repository {
    public:
        /**
         * Creates the repository.
         * @param config is the configuration which the repo uses to get the
         *               dir for files.
         */
        Repository(Config const *config);

        /**
         * Deletes everything the repository is storing.
         */
        ~Repository();

        /**
         * Gives you a texture from a given file. After the first time it gets
         * loaded it stores it for faster loading.
         * @param name is the filename of the texture.
         * @return the texture.
         */
        sf::Texture *getTexture(char const *name);

        /**
         * Gives you a sprite batch from a given file. After the first time it
         * gets loaded it stores it for later.
         * @param name is the filename of the sprite batch.
         * @return the sprite batch.
         */
        SpriteBatch *getSpriteBatch(char const *name);

        /**
         * Gives you a sound buffer from a file or saved you know.
         * @param name is the name of the sound to load.
         * @return a pointer to the sound buffer.
         */
        sf::SoundBuffer *getSound(char const *name);

        /**
         * Gives you a song which is cached.
         * @param name is the name of the song to load and the key to cache it
         *             by.
         * @return a poiinter to the song.
         */
        sf::Music *getSong(char const *name);

        /**
         * Gives you a tileset which is cached.
         * @param name is the name of the tileset to load.
         * @return a pointer to the tileset.
         */
        Tileset const *getTileset(char const *name);

        /**
         * Gives you a tilemap which is cached.
         * @param name is the filename to get it from originally.
         * @return a pointer to the tile map.
         */
        TileMap const *getTileMap(char const *name);

        /**
         * Gives you a pointer to a file as a string.
         * @param name is the name of the text to load.
         * @return a pointer to the text.
         */
        char const *getText(char const *name);

        /**
         * Gives you the game's only font.
         * @return the font which was decided in the game's main config file.
         */
        sf::Font const *getFont();

    private:
        Config const *config;
        sf::Font font;
        std::unordered_map<std::string, sf::Texture *> textures;
        std::unordered_map<std::string, SpriteBatch *> spriteBatches;
        std::unordered_map<std::string, Tileset *> tilesets;
        std::unordered_map<std::string, TileMap *> tileMaps;
        std::unordered_map<std::string, char *> texts;
        std::unordered_map<std::string, sf::SoundBuffer *> sounds;
};

#endif
