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
        std::string const name;
        sf::Vector2u const tileSize;
        sf::FloatRect const bounds;
        Asset<sf::Texture> const &texture;

        /**
         * Creates the tileset from the given data.
         * @param name     is the name of the tileset. This object will take
         *                 care of the string from now on.
         * @param tileSize is the size of tiles in this tileset in terms of the
         *                 rectangles bounding the tile images.
         * @param bounds   is the size of the rectangle bounding the tileset as
         *                 a whole within the texture.
         * @param texture  is a pointer to the texture that is used to render
         *                 the tileset.
         */
        Tileset(
            char const &name,
            sf::Vector2u tileSize,
            sf::FloatRect bounds,
            Asset<sf::Texture> const &texture
        );

        /**
         * Takes four vertices and makes them into a quad for the given tile.
         * @param vertices is a pointer to the first vertex.
         * @param id       is the id of the tile to make.
         */
        void buildQuad(sf::Vertex &vertices, unsigned char id) const;
};

#endif
