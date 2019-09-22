#ifndef TILE_MAP_H
#define TILE_MAP_H

/**
 * Represents a game map as it is loaded from the tiled editor.
 */
class TileMap {
    public:
        /**
         * Creates a tilemap out of an input stream.
         * @param data is the contents of the tiled editor xml file the map is
         *             being loaded from.
         */
        TileMap(char const *data);

    private:
        sf::Vector3i dimensions;
        char *tiles;
};

#endif
