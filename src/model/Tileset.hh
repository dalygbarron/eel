#ifndef TILESET_H
#define TILESET_H

#include "static/xml/pugixml.hpp"
#include <SFML/Graphics.hpp>

// Forward declaration because repo also handles tilesets.
class Repository;

/**
 * Represents a tileset loaded from tiled editor tileset file.
 */
class Tileset {
    public:
        /**
         * Creates the tileset from the given data.
         * @param node       is the tiled xml node of the tileset.
         * @param repository is the asset repository which is used to load the
         *                   tileset's texture.
         */
        Tileset(pugi::xml_node node, Repository *repository);

        /**
         * Deletes the tilset name because that is all it needs to worry about.
         */
        ~Tileset();

        /**
         * Gives the name of the tileset.
         * @return the name.
         */
        char const *getName() const;

        /**
         * Gives the size of a tile in the tileset.
         * @return the size as a vector.
         */
        sf::Vector2i getTileSize() const;

        /**
         * Takes four vertices and makes them into a quad for the given tile.
         * @param vertices is a pointer to the first vertex.
         * @param id       is the id of the tile to make.
         */
        void buildQuad(sf::Vertex *vertices, unsigned char id) const;

        /**
         * Places this texture on top of another texture presumed to be a
         * texture atlas so that all mobs can be rendered in a single draw
         * call. Note that there is a hard coded maximum set of dimensions for
         * a tileset to be applied to a texture atlas, and if this tileset is
         * too big it will log an error and crash.
         * @param atlas is the texture to draw this tileset onto.
         */
        void apply(sf::Texture *atlas) const;

    private:
        char const *name;
        sf::Texture *texture;
        sf::Vector2i tileSize;
        int columns;
};

#endif
