#ifndef TILE_MAP_H
#define TILE_MAP_H

/**
 * Represents a game map as it is loaded from the tiled editor.
 */
class TileMap {
    public:
        /**
         * Creates a tilemap which is totally empty.
         * @param width  is the width of the map.
         * @param height is the height of the map.
         * @param depth  is the depth of the map.
         */
        TileMap(int width, int height, int depth);

        /**
         * Creates a tilemap out of an input stream.
         * @param stream is the input stream to create the file from.
         */
        TileMap(sf::InputStream *stream);

    private:
        int width;
        int height;
        char *tiles;
};

#endif
