#ifndef TILESET_H
#define TILESET_H

#include "service/repository/TextureRepository.hh"
#include "static/xml/pugixml.hpp"
#include <SFML/Graphics.hpp>

/**
 * Represents a tileset loaded from tiled editor tileset file.
 */
class Tileset {
    public:
        /**
         * Creates the tileset from the given data.
         * @param name     is the name of the tileset. This object will take
         *                 care of the string from now on.
         * @param tileSize is the size of tiles in this tileset in terms of the
         *                 rectangles bounding the tile images.
         * @param texture  is a pointer to the texture that is used to render
         *                 the tileset.
         */
        Tileset(
            char const &name,
            sf::Vector2u tileSize,
            Asset<sf::Texture> const &texture
        );

        /**
         * Deletes the tilset name because that is all it needs to worry about.
         */
        ~Tileset();

        /**
         * Gives the name of the tileset.
         * @return the name.
         */
        char const &getName() const;

        /**
         * Gives the size of a tile in the tileset.
         * @return the size as a vector.
         */
        sf::Vector2u getTileSize() const;

        /**
         * Gives you the tileset's rendering texture.
         * @return the texture.
         */
        Asset<sf::Texture> const &getTexture() const;

        /**
         * Takes four vertices and makes them into a quad for the given tile.
         * @param vertices is a pointer to the first vertex.
         * @param id       is the id of the tile to make.
         */
        void buildQuad(sf::Vertex &vertices, unsigned char id) const;

    private:
        char const &name;
        sf::Vector2u tileSize;
        Asset<sf::Texture> const &texture;
};

#endif
